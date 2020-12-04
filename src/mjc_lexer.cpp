#include <mjc_lexer.h>
#include <mjc_reservedwords.h>
#include <mjc_streamio.h>

namespace mjc {

void Lexer::fillInputBuffer() {
  auto totalCharsRead = StreamIO::readCharacters(
      d_inputFile, &d_inputBuffer[d_inputPos], s_InputReadSize);
  if (totalCharsRead < s_InputReadSize) {
    d_inputBuffer[d_inputPos + totalCharsRead] = '\0';
  }
  d_fencePos = (d_inputPos + s_InputReadSize) % s_InputBufferMaxCapacity;
}

std::optional<char> Lexer::nextChar() {
  auto nextC = d_inputBuffer[d_inputPos];
  advance();
  if (nextC == '\0') {
    return std::nullopt;
  }
  if (d_inputPos == d_fencePos) {
    fillInputBuffer();
  }
  return nextC;
}

std::optional<char> Lexer::peek() {
  auto nextC = d_inputBuffer[d_inputPos];
  if (nextC == '\0') {
    return std::nullopt;
  }
  return nextC;
}

void Lexer::advance() {
  d_inputPos = (d_inputPos + 1) % s_InputBufferMaxCapacity;
}

void Lexer::retreat() {
  d_inputPos = (d_inputPos - 1) % s_InputBufferMaxCapacity;
}

void Lexer::rollback() {
  if (d_inputPos == d_fencePos) {
    error("Rollback failed");
  }
  retreat();
}

std::optional<Lexer> Lexer::create(std::string fileName) {
  Status creationStatus;
  Lexer lexer{std::move(fileName), creationStatus};
  return creationStatus == Status::e_OK ? std::make_optional(std::move(lexer))
                                        : std::nullopt;
}

Lexer::Lexer(std::string fileName, Lexer::Status &status)
    : d_inputBuffer(s_InputBufferMaxCapacity, '\0'), d_fileName{
                                                         std::move(fileName)} {
  d_inputFile.open(d_fileName);
  if (d_inputFile) {
    status = Status::e_OK;
    fillInputBuffer();
  } else {
    status = Status::e_FAIL;
  }
}

Token Lexer::nextToken() {
  ReservedWords reservedWords;
  while (true) {
    auto currChar = nextChar();
    if (!currChar) {
      return Token{Token::Kind::e_EOF};
    }
    switch (*currChar) {
    case 'a':
    case 'b':
    case 'c':
    case 'd':
    case 'e':
    case 'f':
    case 'g':
    case 'h':
    case 'i':
    case 'j':
    case 'k':
    case 'l':
    case 'm':
    case 'n':
    case 'o':
    case 'p':
    case 'q':
    case 'r':
    case 's':
    case 't':
    case 'u':
    case 'v':
    case 'w':
    case 'x':
    case 'y':
    case 'z':
    case 'A':
    case 'B':
    case 'C':
    case 'D':
    case 'E':
    case 'F':
    case 'G':
    case 'H':
    case 'I':
    case 'J':
    case 'K':
    case 'L':
    case 'M':
    case 'N':
    case 'O':
    case 'P':
    case 'Q':
    case 'R':
    case 'S':
    case 'T':
    case 'U':
    case 'V':
    case 'W':
    case 'X':
    case 'Y':
    case 'Z':
    case '_': {
      auto id = readIdentifierLike(*currChar);
      if (id == "System"sv) {
        auto rollbackCount = 0;
        auto printlnSuffix = ".out.println"sv;
        bool isPrintln = true;
        for (char c : printlnSuffix) {
          auto nextC = nextChar();
          ++rollbackCount;
          if ((!nextC) || (*nextC != c)) {
            while (rollbackCount > 0) {
              rollback();
              --rollbackCount;
            }
            isPrintln = false;
            break;
          }
        }
        if (isPrintln) {
          return Token{Token::Kind::e_PRINTLN};
        }
      }
      auto keyword = reservedWords.tokenKind(id);
      if (keyword) {
        return Token{*keyword};
      }
      return Token{Token::Kind::e_IDENTIFIER, id};
    } break;

    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9': {
      return Token{Token::Kind::e_INT_LIT, readNaturalNumber(*currChar)};
    } break;

    case ' ':
    case '\f':
    case '\r':
    case '\t':
    case '\v': {
      skipWhiteSpace();
    } break;

    case '\n': {
      ++d_lineNumber;
      skipWhiteSpace();
    } break;

    case '&': {
      currChar = nextChar();
      if (!currChar || *currChar != '&') {
        rollback();
        error();
      }
      return Token{Token::Kind::e_AND};
    } break;

    case '{':
      return Token{Token::Kind::e_LBRACE};

    case '}':
      return Token{Token::Kind::e_RBRACE};

    case '(':
      return Token{Token::Kind::e_LPAREN};

    case ')':
      return Token{Token::Kind::e_RPAREN};

    case '[':
      return Token{Token::Kind::e_LBRACKET};

    case ']':
      return Token{Token::Kind::e_RBRACKET};

    case ';':
      return Token{Token::Kind::e_SEMI};

    case '.':
      return Token{Token::Kind::e_DOT};

    case ',':
      return Token{Token::Kind::e_COMMA};

    case '<':
      return Token{Token::Kind::e_LESSTHAN};

    case '+':
      return Token{Token::Kind::e_PLUS};

    case '-': {
      auto nextC = peek();
      if (nextC && std::isdigit(*nextC)) {
        return Token{Token::Kind::e_INT_LIT, -readNaturalNumber(*nextC)};
      }
      return Token{Token::Kind::e_MINUS};
    } break;

    case '*':
      return Token{Token::Kind::e_TIMES};

    case '!':
      return Token{Token::Kind::e_NOT};

    case '=':
      return Token{Token::Kind::e_ASSIGN};

    default: {
      rollback();
      error();
    } break;
    }
  }
}

void Lexer::skipWhiteSpace() {
  std::optional<char> currChar;
  do {
    currChar = nextChar();
    if (!currChar) {
      rollback();
      return;
    }
    switch (*currChar) {
    case '\n':
      ++d_lineNumber;
    case ' ':
    case '\f':
    case '\r':
    case '\t':
    case '\v':
      break;

    default: {
      rollback();
      return;
    } break;
    }
  } while (true);
}

void Lexer::error(std::string message) {
  auto currChar = nextChar();
  if (message.empty()) {
    std::clog << (currChar.has_value()
                      ? fmt::format("Lexical error at or near {} at {}:{}\n",
                                    *currChar, d_fileName, d_lineNumber)
                      : fmt::format("Lexical error at {}:{}.\n", d_fileName,
                                    d_lineNumber));
  } else {
    std::clog << (currChar.has_value()
                      ? fmt::format("Lexical error at or near {} at {}:{}. "
                                    "Specific error: {}\n",
                                    *currChar, d_fileName, d_lineNumber,
                                    message)
                      : fmt::format(
                            "Lexical error at {}:{}. Specific error: {}\n",
                            d_fileName, d_lineNumber, message));
  }
  std::exit(EXIT_FAILURE);
}

int Lexer::readNaturalNumber(char firstDigit) {
  int number = firstDigit - '0';
  auto currChar = nextChar();
  while (currChar && std::isdigit(*currChar)) {
    number = (number * 10) + (*currChar - '0');
    currChar = nextChar();
  }
  rollback();
  return number;
}
std::string Lexer::readIdentifierLike(char firstChar) {
  std::string id(1, firstChar);
  auto currChar = nextChar();
  while (currChar && (std::isalnum(*currChar) || *currChar == '_')) {
    id.push_back(*currChar);
    currChar = nextChar();
  }
  rollback();
  return id;
}
} // namespace mjc
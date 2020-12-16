#ifndef MJC_LEXER_INCLUDED
#define MJC_LEXER_INCLUDED

#include <fstream>
#include <mjc_lexerprotocol.h>
#include <mjc_reservedwords.h>
#include <optional>
#include <string>

namespace mjc {

class Lexer : public LexerProtocol {
public:
  ~Lexer() override = default;
  static std::optional<Lexer> create(std::string fileName);
  static Lexer create(std::unique_ptr<std::istream> inputFile,
                      std::string fileName);
  Lexer(Lexer &&other) noexcept;
  Lexer &operator=(Lexer &&other) noexcept;
  [[nodiscard]] Token nextToken() override;
  bool success() const noexcept override;
  FilePosition currentPosition() const override;

private:
  static constexpr std::size_t s_InputReadSize = 2048;
  static constexpr std::size_t s_InputBufferMaxCapacity = 2 * s_InputReadSize;

  enum Status { e_SUCCESS, e_FAILURE };

  Lexer(std::unique_ptr<std::istream> inputStream, std::string fileName);
  [[nodiscard]] std::optional<char> nextChar();
  [[nodiscard]] std::optional<char> peek();
  void rollback();
  void advance();
  void retreat();
  void fillInputBuffer();
  void skipWhiteSpace();
  void skipUntilNewLine();
  int readNaturalNumber(char firstDigit);
  std::string readIdentifierLike(char firstChar);
  void error(std::string message = "");
  std::string d_inputBuffer;
  std::size_t d_inputPos{0};
  std::size_t d_fencePos{0};
  std::size_t d_lineNumber{0};
  std::string d_fileName;
  std::unique_ptr<std::istream> d_inputStream;
  Status d_executionStatus{e_SUCCESS};
};

inline Token Lexer::nextToken() {
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
      return Token{Token::Kind::e_INTEGER_LITERAL,
                   readNaturalNumber(*currChar)};
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

    case '/': {
      currChar = nextChar();
      if (!currChar || *currChar != '/') {
        rollback();
        error();
      } else {
        skipUntilNewLine();
      }
    } break;

    case '&': {
      currChar = nextChar();
      if (!currChar || *currChar != '&') {
        rollback();
        error();
      }
      return Token{Token::Kind::e_DOUBLE_AMPERSAND};
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
      return Token{Token::Kind::e_MINUS};
    } break;

    case '*':
      return Token{Token::Kind::e_STAR};

    case '!':
      return Token{Token::Kind::e_BANG};

    case '=':
      return Token{Token::Kind::e_EQUAL};

    default: {
      rollback();
      error();
    } break;
    }
  }
}

inline bool Lexer::success() const noexcept {
  return d_executionStatus == Status::e_SUCCESS;
}

inline FilePosition Lexer::currentPosition() const {
  return {d_fileName, d_lineNumber};
}

inline Lexer::Lexer(Lexer &&other) noexcept
    : d_inputBuffer{std::move(other.d_inputBuffer)},
      d_inputPos{other.d_inputPos}, d_fencePos{other.d_fencePos},
      d_lineNumber{other.d_lineNumber}, d_fileName{std::move(other.d_fileName)},
      d_inputStream{std::move(other.d_inputStream)},
      d_executionStatus{other.d_executionStatus} {}

inline Lexer &Lexer::operator=(Lexer &&other) noexcept {
  d_inputBuffer = std::move(other.d_inputBuffer);
  d_inputPos = other.d_inputPos;
  d_fencePos = other.d_fencePos;
  d_lineNumber = other.d_lineNumber;
  d_fileName = std::move(other.d_fileName);
  d_inputStream = std::move(other.d_inputStream);
  d_executionStatus = other.d_executionStatus;

  return *this;
}

} // namespace mjc

#endif // MJC_LEXER_INCLUDED

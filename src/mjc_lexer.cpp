#include <mjc_lexer.h>
#include <mjc_streamio.h>

namespace mjc {

void Lexer::fillInputBuffer() {
  auto totalCharsRead = StreamIO::readCharacters(
      *d_inputStream, &d_inputBuffer[d_inputPos], s_InputReadSize);
  d_inputBuffer[(d_inputPos + totalCharsRead) % s_InputBufferMaxCapacity] =
      '\0';
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
  auto in = std::unique_ptr<std::istream>(new std::ifstream(fileName));
  if (in->good()) {
    Lexer lexer(std::move(in), std::move(fileName));
    return std::make_optional<Lexer>(std::move(lexer));
  } else {
    return std::nullopt;
  }
}

Lexer Lexer::create(std::unique_ptr<std::istream> inputFile,
                    std::string fileName) {
  return Lexer{std::move(inputFile), std::move(fileName)};
}

Lexer::Lexer(std::unique_ptr<std::istream> inputStream, std::string fileName)
    : d_inputBuffer(s_InputBufferMaxCapacity, '\0'),
      d_fileName{std::move(fileName)}, d_inputStream{std::move(inputStream)} {

  fillInputBuffer();
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

void Lexer::skipUntilNewLine() {
  for (auto currChar = nextChar(); true; currChar = nextChar()) {
    if (!currChar) {
      rollback();
      error();
      return;
    }
    if (*currChar == '\n') {
      return;
    }
  }
}

void Lexer::error(std::string message) {
  auto currChar = nextChar();
  if (message.empty()) {
    std::cerr << (currChar.has_value()
                      ? fmt::format("Lexical error at or near {} at {}:{}\n",
                                    *currChar, d_fileName, d_lineNumber)
                      : fmt::format("Lexical error at {}:{}.\n", d_fileName,
                                    d_lineNumber));
  } else {
    std::cerr << (currChar.has_value()
                      ? fmt::format("Lexical error at or near {} at {}:{}. "
                                    "Specific error: {}\n",
                                    *currChar, d_fileName, d_lineNumber,
                                    message)
                      : fmt::format(
                            "Lexical error at {}:{}. Specific error: {}\n",
                            d_fileName, d_lineNumber, message));
  }
  d_executionStatus = Status::e_FAILURE;
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
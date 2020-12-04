#ifndef MJC_LEXER_INCLUDED
#define MJC_LEXER_INCLUDED

#include <fstream>
#include <mjc_token.h>
#include <optional>
#include <string>

namespace mjc {

class Lexer {
public:
  static std::optional<Lexer> create(std::string fileName);
  [[nodiscard]] Token nextToken();

private:
  static constexpr std::size_t s_InputReadSize = 2048;
  static constexpr std::size_t s_InputBufferMaxCapacity = 2 * s_InputReadSize;

  enum Status { e_OK, e_FAIL };

  Lexer(std::string fileName, Status &status);
  [[nodiscard]] std::optional<char> nextChar();
  [[nodiscard]] std::optional<char> peek();
  void rollback();
  void advance();
  void retreat();
  void fillInputBuffer();
  void skipWhiteSpace();
  int readNaturalNumber(char firstDigit);
  std::string readIdentifierLike(char firstChar);
  [[noreturn]] void error(std::string message = "");
  std::string d_inputBuffer;
  std::size_t d_inputPos{0};
  std::size_t d_fencePos{0};
  std::size_t d_lineNumber{0};
  std::string d_fileName;
  std::ifstream d_inputFile;
};
} // namespace mjc

#endif // MJC_LEXER_INCLUDED

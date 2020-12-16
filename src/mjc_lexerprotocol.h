#ifndef MJC_LEXERPROTOCOL_INCLUDED
#define MJC_LEXERPROTOCOL_INCLUDED

#include <mjc_fileposition.h>
#include <mjc_token.h>

namespace mjc {

struct LexerProtocol {
  virtual ~LexerProtocol() = default;
  [[nodiscard]] virtual Token nextToken() = 0;
  virtual bool success() const noexcept = 0;
  virtual FilePosition currentPosition() const = 0;
};
} // namespace mjc

#endif // MJC_LEXERPROTOCOL_INCLUDED

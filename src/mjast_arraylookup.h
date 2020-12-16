#ifndef MJAST_ARRAYLOOKUP_INCLUDED
#define MJAST_ARRAYLOOKUP_INCLUDED

#include <memory>

namespace mjast {

struct Exp;

struct ArrayLookup {
  std::unique_ptr<Exp> objExp, indexExp;
};

} // namespace mjast

#endif // MJAST_ARRAYLOOKUP_INCLUDED
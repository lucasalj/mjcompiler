#ifndef MJAST_ARRAYLENGTH_INCLUDED
#define MJAST_ARRAYLENGTH_INCLUDED

#include <memory>

namespace mjast {

struct Exp;

struct ArrayLength {
  std::unique_ptr<Exp> objExp;
};

} // namespace mjast

#endif // MJAST_ARRAYLENGTH_INCLUDED
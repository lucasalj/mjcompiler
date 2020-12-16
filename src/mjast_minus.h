#ifndef MJAST_MINUS_INCLUDED
#define MJAST_MINUS_INCLUDED

#include <memory>

namespace mjast {

struct Exp;

struct Minus {
  std::unique_ptr<Exp> e1, e2;
};

} // namespace mjast

#endif // MJAST_MINUS_INCLUDED
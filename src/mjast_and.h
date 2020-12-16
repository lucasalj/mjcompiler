#ifndef MJAST_AND_INCLUDED
#define MJAST_AND_INCLUDED

#include <memory>

namespace mjast {

struct Exp;

struct And {
  std::unique_ptr<Exp> e1, e2;
};

} // namespace mjast

#endif // MJAST_AND_INCLUDED
#ifndef MJAST_TIMES_INCLUDED
#define MJAST_TIMES_INCLUDED

#include <memory>

namespace mjast {

struct Exp;

struct Times {
  std::unique_ptr<Exp> e1, e2;
};

} // namespace mjast

#endif // MJAST_TIMES_INCLUDED
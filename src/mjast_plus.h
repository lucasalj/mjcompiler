#ifndef MJAST_PLUS_INCLUDED
#define MJAST_PLUS_INCLUDED

#include <memory>

namespace mjast {

struct Exp;

struct Plus {
  std::unique_ptr<Exp> e1, e2;
};

} // namespace mjast

#endif // MJAST_PLUS_INCLUDED

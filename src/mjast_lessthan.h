#ifndef MJAST_LESSTHAN_INCLUDED
#define MJAST_LESSTHAN_INCLUDED

#include <memory>

namespace mjast {

struct Exp;

struct LessThan {
  std::unique_ptr<Exp> e1, e2;
};

} // namespace mjast

#endif // MJAST_LESSTHAN_INCLUDED
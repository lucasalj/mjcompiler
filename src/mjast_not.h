#ifndef MJAST_NOT_INCLUDED
#define MJAST_NOT_INCLUDED

#include <memory>

namespace mjast {

struct Exp;

struct Not {
  std::unique_ptr<Exp> exp;
};

} // namespace mjast

#endif // MJAST_NOT_INCLUDED
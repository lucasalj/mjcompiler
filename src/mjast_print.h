#ifndef MJAST_PRINT_INCLUDED
#define MJAST_PRINT_INCLUDED

#include <memory>

namespace mjast {

struct Exp;

struct Print {

  std::unique_ptr<Exp> exp;
};

} // namespace mjast

#endif // MJAST_PRINT_INCLUDED
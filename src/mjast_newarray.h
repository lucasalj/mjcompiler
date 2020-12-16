#ifndef MJAST_NEWARRAY_INCLUDED
#define MJAST_NEWARRAY_INCLUDED

#include <memory>

namespace mjast {

struct Exp;

struct NewArray {
  std::unique_ptr<Exp> sizeExp;
};

} // namespace mjast

#endif // MJAST_NEWARRAY_INCLUDED
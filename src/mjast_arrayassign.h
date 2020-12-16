#ifndef MJAST_ARRAYASSIGN_INCLUDED
#define MJAST_ARRAYASSIGN_INCLUDED

#include <memory>

namespace mjast {
struct Identifier;
struct Exp;
struct ArrayAssign {
  std::unique_ptr<Identifier> name;
  std::unique_ptr<Exp> indexExp, valueExp;
};
} // namespace mjast

#endif // MJAST_ARRAYASSIGN_INCLUDED
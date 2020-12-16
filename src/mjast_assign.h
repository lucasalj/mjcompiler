#ifndef MJAST_ASSIGN_INCLUDED
#define MJAST_ASSIGN_INCLUDED

#include <memory>

namespace mjast {

struct Identifier;
struct Exp;

struct Assign {
  std::unique_ptr<Identifier> name;
  std::unique_ptr<Exp> valueExp;
};
} // namespace mjast

#endif // MJAST_ASSIGN_INCLUDED
#ifndef MJAST_FORMAL_INCLUDED
#define MJAST_FORMAL_INCLUDED

#include <memory>

namespace mjast {

struct Type;
struct Identifier;

struct Formal {
  std::unique_ptr<Type> typ;
  std::unique_ptr<Identifier> name;
};

} // namespace mjast

#endif // MJAST_FORMAL_INCLUDED
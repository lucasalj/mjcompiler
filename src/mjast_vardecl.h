#ifndef MJAST_VARDECL_INCLUDED
#define MJAST_VARDECL_INCLUDED

#include <memory>

namespace mjast {

struct Type;
struct Identifier;

struct VarDecl {
  std::unique_ptr<Type> typ;
  std::unique_ptr<Identifier> name;
};

} // namespace mjast

#endif // MJAST_VARDECL_INCLUDED
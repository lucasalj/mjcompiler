#ifndef MJAST_CLASSDECLEXTENDS_INCLUDED
#define MJAST_CLASSDECLEXTENDS_INCLUDED

#include <memory>

namespace mjast {

struct Identifier;
struct VarDeclList;
struct MethodDeclList;

struct ClassDeclExtends {
  std::unique_ptr<Identifier> name, parentName;
  std::unique_ptr<VarDeclList> vars;
  std::unique_ptr<MethodDeclList> methods;
};

} // namespace mjast

#endif // MJAST_CLASSDECLEXTENDS_INCLUDED
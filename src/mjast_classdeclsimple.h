#ifndef MJAST_CLASSDECLSIMPLE_INCLUDED
#define MJAST_CLASSDECLSIMPLE_INCLUDED

#include <memory>

namespace mjast {

struct Identifier;
struct VarDeclList;
struct MethodDeclList;

struct ClassDeclSimple {
  std::unique_ptr<Identifier> name;
  std::unique_ptr<VarDeclList> vars;
  std::unique_ptr<MethodDeclList> methods;
};

} // namespace mjast

#endif // MJAST_CLASSDECLSIMPLE_INCLUDED
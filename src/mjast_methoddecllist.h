#ifndef MJAST_METHODDECLLIST_INCLUDED
#define MJAST_METHODDECLLIST_INCLUDED

#include <memory>
#include <vector>

namespace mjast {

struct MethodDecl;

struct MethodDeclList {
  std::vector<std::unique_ptr<MethodDecl>> methods;
};

} // namespace mjast

#endif // MJAST_METHODDECLLIST_INCLUDED
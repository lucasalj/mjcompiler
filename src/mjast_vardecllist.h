#ifndef MJAST_VARDECLLIST_INCLUDED
#define MJAST_VARDECLLIST_INCLUDED

#include <memory>
#include <vector>

namespace mjast {

struct VarDecl;

struct VarDeclList {
  std::vector<std::unique_ptr<VarDecl>> varDecls;
};

} // namespace mjast

#endif // MJAST_VARDECLLIST_INCLUDED

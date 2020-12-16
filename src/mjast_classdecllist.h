#ifndef MJAST_CLASSDECLLIST_INCLUDED
#define MJAST_CLASSDECLLIST_INCLUDED

#include <memory>
#include <vector>

namespace mjast {

struct ClassDecl;

struct ClassDeclList {
  std::vector<std::unique_ptr<ClassDecl>> list;
};

} // namespace mjast

#endif // MJAST_CLASSDECLLIST_INCLUDED
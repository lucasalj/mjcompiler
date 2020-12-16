#ifndef MJAST_CLASSDECL_INCLUDED
#define MJAST_CLASSDECL_INCLUDED

#include <mjast_classdeclextends.h>
#include <mjast_classdecllist.h>
#include <mjast_classdeclsimple.h>
#include <mjc_variant.h>

namespace mjast {

struct ClassDecl : public mjc::Variant<ClassDeclExtends, ClassDeclSimple> {
  using mjc::Variant<ClassDeclExtends, ClassDeclSimple>::Variant;
};

} // namespace mjast

#endif // MJAST_CLASSDECL_INCLUDED
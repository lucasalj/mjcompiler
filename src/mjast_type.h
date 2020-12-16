#ifndef MJAST_TYPE_INCLUDED
#define MJAST_TYPE_INCLUDED

#include <mjast_booleantype.h>
#include <mjast_identifiertype.h>
#include <mjast_intarraytype.h>
#include <mjast_integertype.h>
#include <mjc_variant.h>

namespace mjast {

struct Type : public mjc::Variant<IntArrayType, BooleanType, IntegerType,
                                  IdentifierType> {
  using mjc::Variant<IntArrayType, BooleanType, IntegerType,
                     IdentifierType>::Variant;
};

} // namespace mjast

#endif // MJAST_TYPE_INCLUDED
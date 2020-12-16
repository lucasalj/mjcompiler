#ifndef MJAST_EXP_INCLUDED
#define MJAST_EXP_INCLUDED

#include <mjast_and.h>
#include <mjast_arraylength.h>
#include <mjast_arraylookup.h>
#include <mjast_call.h>
#include <mjast_false.h>
#include <mjast_identifierexp.h>
#include <mjast_integerliteral.h>
#include <mjast_lessthan.h>
#include <mjast_minus.h>
#include <mjast_newarray.h>
#include <mjast_newobject.h>
#include <mjast_not.h>
#include <mjast_plus.h>
#include <mjast_this.h>
#include <mjast_times.h>
#include <mjast_true.h>
#include <mjc_variant.h>

namespace mjast {

struct Exp
    : public mjc::Variant<And, LessThan, Plus, Minus, Times, ArrayLookup,
                          ArrayLength, Call, IntegerLiteral, True, False,
                          IdentifierExp, This, NewArray, NewObject, Not> {
  using mjc::Variant<And, LessThan, Plus, Minus, Times, ArrayLookup,
                     ArrayLength, Call, IntegerLiteral, True, False,
                     IdentifierExp, This, NewArray, NewObject, Not>::Variant;
};

} // namespace mjast

#endif // MJAST_EXP_INCLUDED
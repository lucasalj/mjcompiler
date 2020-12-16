#ifndef MJAST_STATEMENT_INCLUDED
#define MJAST_STATEMENT_INCLUDED

#include <mjast_arrayassign.h>
#include <mjast_assign.h>
#include <mjast_block.h>
#include <mjast_if.h>
#include <mjast_print.h>
#include <mjast_while.h>
#include <mjc_variant.h>

namespace mjast {

struct Statement
    : public mjc::Variant<Block, If, While, Print, Assign, ArrayAssign> {
  using mjc::Variant<Block, If, While, Print, Assign, ArrayAssign>::Variant;
};

} // namespace mjast

#endif // MJAST_STATEMENT_INCLUDED
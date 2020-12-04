#ifndef MJC_ASSERT_INCLUDED
#define MJC_ASSERT_INCLUDED

#include <debug_assert.hpp>

#ifndef MJC_DEFAULT_ASSERTION_LEVEL
#define MJC_DEFAULT_ASSERTION_LEVEL 2
#endif // MJC_DEFAULT_ASSERTION_LEVEL

#define MJC_ASSERT_ALWAYS(Expr, module, ...)                                   \
  DEBUG_ASSERT(Expr, module, debug_assert::level<1>{}, __VA_ARGS__)

#define MJC_ASSERT_DEBUG(Expr, module, ...)                                    \
  DEBUG_ASSERT(Expr, module, debug_assert::level<2>{}, __VA_ARGS__)

#define MJC_ASSERT_DEBUG_COMPLEX(Expr, module, ...)                            \
  DEBUG_ASSERT(Expr, module, debug_assert::level<3>{}, __VA_ARGS__)

namespace mjc {
struct DefaultAssertionHandler
    : debug_assert::default_handler,
      debug_assert::set_level<MJC_DEFAULT_ASSERTION_LEVEL> {};

} // namespace mjc

#endif // MJC_ASSERT_INCLUDED
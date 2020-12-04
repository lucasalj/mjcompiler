#ifndef MJC_LOGGINGASSERTIONHANDLER_INCLUDED
#define MJC_LOGGINGASSERTIONHANDLER_INCLUDED

#include <fmt/format.h>
#include <iostream>
#include <mjc_assert.h>

namespace mjc {

struct LoggingAssertionHandler
    : debug_assert::set_level<MJC_DEFAULT_ASSERTION_LEVEL> {

  template <typename... T>
  static void handle(const debug_assert::source_location &loc,
                     const char *expression, char const *format,
                     T &&... values) noexcept;
};

template <typename... T>
void LoggingAssertionHandler::handle(const debug_assert::source_location &loc,
                                     const char *expression, char const *format,
                                     T &&... values) noexcept {
  std::clog << "Assertion failed: \"" << expression << "\" Message: "
            << fmt::format(format, std::forward<T>(values)...);
}

} // namespace mjc

#endif // MJC_LOGGINGASSERTIONHANDLER_INCLUDED
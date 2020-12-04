find_package(fmt CONFIG REQUIRED)
find_package(magic_enum CONFIG REQUIRED)

add_library(mjc mjc_traits.cpp mjc_overloadset.cpp mjc_token.cpp mjc_assert.cpp mjc_loggingassertionhandler.cpp mjc_streamio.cpp mjc_reservedwords.cpp mjc_lexer.cpp)

target_include_directories(mjc PUBLIC ./)
target_compile_features(mjc PRIVATE cxx_std_17)
target_link_libraries(mjc PRIVATE fmt::fmt fmt::fmt-header-only
                          PRIVATE magic_enum::magic_enum
                          PUBLIC debug_assert)

find_package(Catch2 CONFIG REQUIRED)

configure_file(files/factorial.java ${CMAKE_CURRENT_BINARY_DIR}/files/factorial.java COPYONLY)

add_executable(mjc_tests mjc_tests.cpp mjc_token_test.cpp mjc_lexer_test.cpp mjc_stringtable_test.cpp)

target_compile_features(mjc_tests PRIVATE cxx_std_17)
target_link_libraries(mjc_tests PRIVATE Catch2::Catch2
                                PRIVATE mjc)

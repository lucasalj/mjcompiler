add_executable(mjclexer mjclexer.cpp)

target_compile_features(mjclexer PRIVATE cxx_std_17)
target_link_libraries(mjclexer PRIVATE mjc)

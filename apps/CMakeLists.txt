find_package(clipp CONFIG REQUIRED)
find_package(range-v3 CONFIG REQUIRED)
find_path(CTRE_INCLUDE_DIRS "ctll.hpp")

add_executable(mjclexer mjclexer.cpp)

target_compile_features(mjclexer PRIVATE cxx_std_17)
target_link_libraries(mjclexer PRIVATE mjc
                               PRIVATE clipp::clipp)

add_executable(mjcparser mjcparser.cpp)

target_compile_features(mjcparser PRIVATE cxx_std_17)
target_include_directories(mjcparser PRIVATE PRIVATE ${CTRE_INCLUDE_DIRS})
target_link_libraries(mjcparser PRIVATE mjc
                                PRIVATE clipp::clipp
                                PRIVATE range-v3 range-v3-meta range-v3::meta range-v3-concepts)


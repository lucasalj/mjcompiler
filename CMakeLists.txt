cmake_minimum_required(VERSION 3.11..3.19)
project(mjcompiler VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_EXTENSIONS OFF)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(libs)

add_subdirectory(src)

add_subdirectory(apps)

include(CTest)
enable_testing()
add_subdirectory(tests)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

cmake_minimum_required(VERSION 3.27)
project(EzLogger)

set(CMAKE_CXX_STANDARD 23)

option(EZLOGGER_BUILD_TESTS "If set to true will build tests of this library" ON)

if (EZLOGGER_BUILD_TESTS EQUAL ON)
    message(STATUS "Enabling CTest on EzLogger")
    enable_testing()
endif ()

add_subdirectory("src")
add_subdirectory("tests")
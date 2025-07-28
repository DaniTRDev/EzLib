cmake_minimum_required(VERSION 3.27)
project(EzLib)

set(CMAKE_CXX_STANDARD 23)
set(EZLIB_COMMON_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Common" CACHE STRING "Path to Common.h directory used by EzLib modules" FORCE)

option(EZLIB_BUILD_TESTS "Builds tests for EzLib" ON)
option(EZLIB_BUILD_STATIC "Build EzLib and its components as STATIC libraries" ON)

if (EZLIB_BUILD_TESTS)
    message(STATUS "Enabling CTest on EzLib")
    include("CMake/Tests.cmake")
    enable_testing()
endif ()

add_subdirectory("EzLogger")
#add_subdirectory("EzLayoutEngine")
#add_subdirectory("EzUIEngine")
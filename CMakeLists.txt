cmake_minimum_required(VERSION 3.28)
project(EzLib)

set(CMAKE_CXX_STANDARD 20)
set(EZLIB_COMMON_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Common" CACHE STRING "Path to Common directory used by EzLib modules" FORCE)

option(EZLIB_BUILD_TESTS "Builds tests for EzLib" OFF)
option(EZLIB_BUILD_STATIC "Build EzLib and its components as STATIC libraries" ON)

# Bootstrap at the beginning.
add_subdirectory(EzCMK)
EzCMK_Bootstrap()

if (EZLIB_BUILD_TESTS)
    EzCMK_EnableTestsForProject(EzLib)
endif ()

if (EZLIB_BUILD_STATIC)
    EzCMK_SetLibraryBuildType("STATIC")
else ()
    EzCMK_SetLibraryBuildType("SHARED")
endif ()

add_subdirectory("EzLogger")
#add_subdirectory("EzLayoutEngine")
#add_subdirectory("EzUIEngine")

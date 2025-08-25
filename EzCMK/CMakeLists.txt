# This file represents the entry point for our CMake scripts that will be available for the project
# that included EzCMK and the rest of the projects.

cmake_minimum_required(VERSION 3.29)
project(EZCMK_PROJECT)

message(STATUS "Loading EzCMK with CMake ${CMAKE_VERSION}")

option(EZCMK_TESTING "Should EzCMK build ALL tests of every sub project?" OFF)
option(EZCMK_INTERNAL_TESTING "Should EzCMK run its own internal tests to ensure it works properly?" OFF)

include(TargetProjectCreator.cmake)
include(Library.cmake)
include(Executable.cmake)
include(Vendor.cmake)
include(Testing.cmake)
include(Bootstrapper.cmake)

if (EZCMK_TESTING)
    message(STATUS "Building TESTS for EVERY EzCMK target")
    enable_testing()
endif ()

if (EZCMK_INTERNAL_TESTING)
    add_subdirectory(tests)
endif ()
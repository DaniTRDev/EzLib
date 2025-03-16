set(EZUI_ENGINE_BUILD "SHARED")

if (EZLIB_BUILD_STATIC)
    set(EZUI_ENGINE_BUILD "STATIC")
endif()

message(STATUS "Building EzUIEngine as ${EZUI_ENGINE_BUILD}")

add_library("EzUIEngine" ${EZUI_ENGINE_BUILD}
)

target_include_directories("EzUIEngine" PUBLIC ${EZLIB_COMMON_PATH})
target_include_directories("EzUIEngine" PUBLIC "include")

if (EZLIB_BUILD_TESTS)
    message(STATUS "Adding tests for EzUIEngine")
    add_subdirectory(tests) # Build tests (only if set)
endif ()
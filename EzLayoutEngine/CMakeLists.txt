add_library("EzLayoutEngine"
        "include/EzLayoutEngine.h"
        "include/ILayout.h"
        "include/Clipping/Clipper.h"
        "include/Layouts/BasicLayout.h"
        "include/Layouts/GridDivider.h"
        "include/Layouts/HorizontalDivider.h"
        "include/Layouts/ILayoutDivider.h"
        "include/Layouts/VerticalDivider.h"
        "include/Primitives/Vec2.h"

        "src/Clipping/Clipper.cpp"
        "src/Layouts/BasicLayout.cpp"
        "src/Layouts/GridDivider.cpp"
        "src/Layouts/HorizontalDivider.cpp"
        "src/Layouts/VerticalDivider.cpp"
        "src/Primitives/Vec2.cpp"
)

target_include_directories("EzLayoutEngine" PUBLIC ${EZLIB_COMMON_PATH})
target_include_directories("EzLayoutEngine" PUBLIC "include")

if (EZLIB_BUILD_TESTS)
    message(STATUS "Adding tests for EzLayoutEngine")
    add_subdirectory(tests) # Build tests (only if set)
endif ()

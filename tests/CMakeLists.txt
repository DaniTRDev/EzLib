
function(EzLogger_AddTest testName testDefinitions testDependencies testFiles)

    if (NOT DEFINED EZLOGGER_BUILD_TESTS OR EZLOGGER_BUILD_TESTS EQUAL OFF)
        return()
    endif ()

    add_executable("${testName}" ${testFiles})
    target_compile_definitions("${testName}" PUBLIC ${testDefinitions})
    target_link_libraries("${testName}" PUBLIC ${testDependencies})

    message(STATUS "Adding test ${testName}")
    add_test("${testName}" "${testName}")

endfunction()

if (DEFINED EZLOGGER_BUILD_TESTS AND EZLOGGER_BUILD_TESTS EQUAL ON)
    message(DEBUG "Building tests for EzLogger")
endif ()

EzLogger_AddTest("ConsoleTest" "" "EzLogger" "ConsoleTest.cpp")
EzLogger_AddTest("FileTest" "" "EzLogger" "FileTest.cpp")
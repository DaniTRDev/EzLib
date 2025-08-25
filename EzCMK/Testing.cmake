# This file is used to have a common interface between all tests.

function(EzCMK_AreTestsEnabledForTarget TARGET_NAME OUT_VAR)
    if (DEFINED "EZCMK_TESTS_ARE_ENABLED_FOR_PROJECT_${EZCMK_CALLER_PROJECT_NAME}")
        set(${OUT_VAR} ON PARENT_SCOPE)
    elseif (DEFINED "EZCMK_TESTS_ARE_ENABLED_FOR_TARGET_${TARGET_NAME}")
        set(${OUT_VAR} ON PARENT_SCOPE)
    elseif (EZCMK_TESTING)
        set(${OUT_VAR} ON PARENT_SCOPE)
    else ()
        set(${OUT_VAR} OFF PARENT_SCOPE)
    endif ()
endfunction()

function(EzCMK_EnableTestsForProject PROJECT_NAME)
    message(STATUS "Enabled tests for ${PROJECT_NAME}")
    set(EZCMK_TESTS_ARE_ENABLED_FOR_PROJECT_${PROJECT_NAME} ON PARENT_SCOPE)
endfunction()

function(EzCMK_EnableTestsForCurrentProject)
    message(STATUS "Enabled tests for ${EZCMK_CALLER_PROJECT_NAME}")
    set("EZCMK_TESTS_ARE_ENABLED_FOR_PROJECT_${EZCMK_CALLER_PROJECT_NAME}" ON PARENT_SCOPE)
endfunction()

function(EzCMK_EnableTestsForTarget TARGET_NAME)
    set(EZCMK_TESTS_ARE_ENABLED_FOR_TARGET_${TARGET_NAME} ON PARENT_SCOPE)
endfunction()

# Adds a test, if tests are enabled for given target. It creates the test with the given name, files and imported libraries.
# TESTED_TARGET is automatically added to TEST_LIBRARIES so it shouldn't be included twice
function(EzCMK_AddTest)
    set(options)  # no boolean switches
    set(oneValueArgs TESTED_TARGET TEST_NAME)
    set(multiValueArgs TEST_FILES TEST_LIBRARIES)
    cmake_parse_arguments("ARG" "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    EzCMK_AreTestsEnabledForTarget(ARG_TESTED_TARGET ENABLE)

    if (ENABLE)
        set(TEST_TARGET_NAME ${ARG_TESTED_TARGET}_${ARG_TEST_NAME})

        message(STATUS "Adding test ${ARG_TEST_NAME} for ${ARG_TESTED_TARGET}")
        EzCMK_AddExecutable(NAME ${TEST_TARGET_NAME}
                FILE_LIST ${ARG_TEST_FILES}
                LINKED_LIBRARIES "${ARG_TESTED_TARGET} ${ARG_TEST_LIBRARIES}")

        add_test(NAME ${ARG_TEST_NAME} COMMAND ${TEST_TARGET_NAME})
    endif ()

endfunction()
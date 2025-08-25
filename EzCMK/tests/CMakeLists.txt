function(CreateTargetTest)
    set(TARGET_PATH "${CMAKE_CURRENT_SOURCE_DIR}/TEST_TARGET")
    set(INCLUDE_DIRECTORY "${TARGET_PATH}/${EZCMK_PROJECT_INCLUDE_PATH}")
    set(SRC_DIRECTORY "${TARGET_PATH}/${EZCMK_PROJECT_SRC_PATH}")
    set(CMAKELISTS "${TARGET_PATH}/CMakeLists.txt")
    set(PRECOMPILED_HEADER "${INCLUDE_DIRECTORY}/PreCompiledHeader.h")

    if (IS_DIRECTORY "${TARGET_PATH}")
        message(STATUS "Clearing previous test")
        file(REMOVE_RECURSE "${TARGET_PATH}")
    endif ()

    # This test will ensure that the test is correctly created after calling CreateTarget.
    EzCMK_CreateTarget(TEST_TARGET "${CMAKE_CURRENT_SOURCE_DIR}" WAS_TARGET_CREATED)
    if (NOT WAS_TARGET_CREATED)
        message(STATUS "Test target was not created properly. Reasons:")
    endif ()

    if (NOT IS_DIRECTORY "${INCLUDE_DIRECTORY}")
        message(FATAL_ERROR "CreateTargetTest - Create include directory failed!")
    endif ()

    if (NOT IS_DIRECTORY "${SRC_DIRECTORY}")
        message(FATAL_ERROR "CreateTargetTest - Create src directory failed!")
    endif ()

    if (NOT EXISTS "${CMAKELISTS}")
        message(FATAL_ERROR "CreateTargetTest - Create CMakeLists.txt failed!")
    endif ()

    if (NOT EXISTS "${PRECOMPILED_HEADER}")
        message(FATAL_ERROR "CreateTargetTest - Create precompiled header failed!")
    endif ()
endfunction()

function(CreateExistingTarget)
    # This test ensure that target was not created because it already existed.
    EzCMK_CreateTarget(EXISTING_TEST_TARGET "${CMAKE_CURRENT_SOURCE_DIR}" WAS_TARGET_CREATED)
    if (WAS_TARGET_CREATED)
        message(STATUS "Test target was not created properly. Reasons:")
    endif ()

    add_subdirectory(EXISTING_TEST_TARGET)

    if (NOT EXISTING_TEST_TARGET_CREATED_INTERNAL)
        message(FATAL_ERROR "CreateExistingTarget - CMakeLists.txt of the existing target was altered!")
    endif ()

endfunction()

CreateTargetTest()
CreateExistingTarget()
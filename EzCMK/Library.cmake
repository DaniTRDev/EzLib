# File used to agglomerate functions that are used to build libraries.

function(EzCMK_GetLibraryTargetName NAME OUT_VAR)
    set(${OUT_VAR} "EzCMK_${NAME}_Library" PARENT_SCOPE)
endfunction()

# Returns in OUT_VAR if given library is built as a SHARED library. If FORCE_VALUE is set, it will always return ${FORCE_VALUE}.
function(EzCMK_GetLibraryBuildType)
    set(options)  # no boolean switches
    set(oneValueArgs OUT_VAR FORCE_VALUE)
    set(multiValueArgs)
    cmake_parse_arguments("ARG" "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if (DEFINED ARG_FORCE_VALUE)
        if (NOT ARG_FORCE_VALUE STREQUAL "")
            set(${ARG_OUT_VAR} ${ARG_FORCE_VALUE} PARENT_SCOPE)
        endif ()
    else ()
        set(FULL_VAR_NAME "EZCMK_PROJECT_${EZCMK_CALLER_PROJECT_NAME}_BUILD_TYPE")
        set(PROJECT_BUILD_TYPE ${${FULL_VAR_NAME}})
        set(${ARG_OUT_VAR} ${PROJECT_BUILD_TYPE} PARENT_SCOPE)
    endif ()
endfunction()

function(EzCMK_SetLibraryBuildType VALUE)
    set(FULL_VAR_NAME "EZCMK_PROJECT_${EZCMK_CALLER_PROJECT_NAME}_BUILD_TYPE")
    set(${FULL_VAR_NAME} ${VALUE} PARENT_SCOPE)
    message(STATUS "Setting default lib build type of project ${EZCMK_CALLER_PROJECT_NAME} to ${FULL_VAR_NAME} = ${VALUE}")
endfunction()

# Tries to create a target with the given name (if not already created)
# It also tries to configure the existing or created target with the options given.
# If SHARED_LIB is not set, it will use the value of EZCMK_BUILD_SHARED_LIBS.
function(EzCMK_ConfigureLib)
    set(options)  # no boolean switches
    set(oneValueArgs NAME PRECOMPILED_HEADER BUILD_TYPE FORCE_CREATION)
    set(multiValueArgs FILE_LIST MODULE_FILES LINKED_LIBRARIES INCLUDED_DIRS DEFINITIONS)
    cmake_parse_arguments("ARG" "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if (DEFINED ARG_FORCE_CREATION AND ARG_FORCE_CREATION)
        EzCMK_CreateTarget(NAME ${ARG_NAME}
                TARGET_DIR_PATH ${CMAKE_CURRENT_SOURCE_DIR}
        )
    endif ()

    EzCMK_GetLibraryTargetName(${ARG_NAME} TARGET_NAME)
    EzCMK_GetLibraryBuildType(OUT_VAR TARGET_BUILD_TYPE
            FORCE_VALUE ${ARG_BUILD_TYPE}
    )

    message(STATUS "Configuring LIBRARY ${ARG_NAME} (target: ${TARGET_NAME}) (build type: ${TARGET_BUILD_TYPE})")

    # 1. Create target without hardcoding sources directly into add_library
    add_library(${ARG_NAME} ${TARGET_BUILD_TYPE})
    add_library(${TARGET_NAME} ALIAS ${ARG_NAME})

    set_target_properties(${ARG_NAME} PROPERTIES OUTPUT_NAME "${ARG_NAME}")

    # 2. Add regular implementation/source files (.cpp)
    if (ARG_FILE_LIST)
        target_sources(${ARG_NAME} PRIVATE ${ARG_FILE_LIST})
    endif ()

    # 3. Add C++20 Module Interfaces and Partitions (.cppm)
    if (ARG_MODULE_FILES)
        target_sources(${ARG_NAME}
            PUBLIC
                FILE_SET CXX_MODULES FILES ${ARG_MODULE_FILES}
        )
        message(VERBOSE "C++20 Module interfaces: ${ARG_MODULE_FILES}")
    endif ()

    if (ARG_LINKED_LIBRARIES)
        target_link_libraries(${ARG_NAME} PUBLIC ${ARG_LINKED_LIBRARIES})
        message(VERBOSE "Library dependencies: ${ARG_LINKED_LIBRARIES}")
    endif ()

    if (ARG_INCLUDED_DIRS)
        target_include_directories(${ARG_NAME} PUBLIC ${ARG_INCLUDED_DIRS})
        message(VERBOSE "Included directories: ${ARG_INCLUDED_DIRS}")
    endif ()

    if (ARG_DEFINITIONS)
        message(VERBOSE "Definitions: ${ARG_DEFINITIONS}")
        target_compile_definitions(${ARG_NAME} PUBLIC ${ARG_DEFINITIONS})
    endif ()

    # 4. Safe check so passing PRECOMPILED_HEADER "" does not trigger an error
    if (ARG_PRECOMPILED_HEADER AND NOT ARG_PRECOMPILED_HEADER STREQUAL "")
        message(VERBOSE "Precompiled header: ${ARG_PRECOMPILED_HEADER}")
        target_precompile_headers(${ARG_NAME} PUBLIC ${ARG_PRECOMPILED_HEADER})
    endif ()
endfunction()

function(EzCMK_LibCompileOption NAME OPTION_NAME CONTENT)
    EzCMK_GetLibraryTargetName(${NAME} TARGET_NAME)
    message(STATUS "Defining compile option for TARGET_NAME named ${OPTION_NAME} with content ${CONTENT}")
    target_compile_options(TARGET_NAME "$<$<CONFIG:${OPTION_NAME}>:${CONTENT}>")
endfunction()


# File used to agglomerate functions that are used to build executables.

function(EzCMK_GetExecutableTargetName NAME OUT_VAR)
    set(${OUT_VAR} "EzCMK_${NAME}_Executable" PARENT_SCOPE)
endfunction()

# Tries to create a target with the given name (if not already created)
# It also tries to configure the existing or created target with the options given.
function(EzCMK_AddExecutable)
    set(options)  # no boolean switches
    set(oneValueArgs NAME PRECOMPILED_HEADER)
    set(multiValueArgs FILE_LIST LINKED_LIBRARIES INCLUDED_DIRS DEFINITIONS)
    cmake_parse_arguments("ARG" "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if (DEFINED ARG_FORCE_CREATION)
        if (ARG_FORCE_CREATION)
            EzCMK_CreateTarget(NAME ${ARG_NAME}
                    TARGET_DIR_PATH ${CMAKE_CURRENT_SOURCE_DIR}
            )
        endif ()
    endif ()
    EzCMK_GetExecutableTargetName(${ARG_NAME} TARGET_NAME)

    message(STATUS "Configuring executable ${ARG_NAME} (target: ${TARGET_NAME})")

    # Define an alias
    add_executable(${ARG_NAME} ${ARG_FILE_LIST})
    add_executable(${TARGET_NAME} ALIAS ${ARG_NAME}) # Use our library

    set_target_properties(${ARG_NAME} PROPERTIES OUTPUT_NAME "${ARG_NAME}")

    if (DEFINED ARG_LINKED_LIBRARIES)
        target_link_libraries(${ARG_NAME} PUBLIC ${ARG_LINKED_LIBRARIES})
        message(VERBOSE "Executable dependencies: ${ARG_LINKED_LIBRARIES}")
    endif ()

    if (DEFINED ARG_INCLUDED_DIRS)
        target_include_directories(${ARG_NAME} PUBLIC ${ARG_INCLUDED_DIRS})
        message(VERBOSE "Included directories: ${ARG_INCLUDED_DIRS}")
    endif ()

    if (DEFINED ARG_DEFINITIONS)
        message(VERBOSE "Definitions: ${ARG_DEFINITIONS}")
        target_compile_definitions(${ARG_NAME} PUBLIC ${ARG_DEFINITIONS})
    endif ()

    if (DEFINED ARG_PRECOMPILED_HEADER)
        message(VERBOSE "Precompiled header: ${ARG_PRECOMPILED_HEADER}")
        target_precompile_headers(${ARG_NAME} PUBLIC ${ARG_PRECOMPILED_HEADER})
    endif ()
endfunction()

function(EzCMK_ExecutableCompileOption NAME OPTION_NAME CONTENT)
    EzCMK_GetExecutableTargetName(${NAME} TARGET_NAME)
    target_compile_options(TARGET_NAME "$<$<CONFIG:${OPTION_NAME}>:${CONTENT}>")
    message(STATUS "Defined compile option for TARGET_NAME named ${OPTION_NAME} with content ${CONTENT}")
endfunction()

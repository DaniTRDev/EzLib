# File that contains code used to wrap module importation. At the moment everything's handled with FetchContent


function(EzCMK_AddVendor LIB_GIT_REPO LIB_GIT_TAG TARGET_NAME)
    message(STATUS "Importing ${GIT_REPO}:${GIT_TAG} with name ${TARGET_NAME}")
    FetchContent_Declare(
            ${TARGET_NAME}
            GIT_REPOSITORY ${LIB_GIT_REPO}
            GIT_TAG ${LIB_GIT_TAG}
    )
    FetchContent_MakeAvailable(${TARGET_NAME})
endfunction()

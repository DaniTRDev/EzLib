# File that will bootstrap EzCMK into the caller project

function(EzCMK_Bootstrap)
    set(EZCMK_CALLER_PROJECT_NAME ${PROJECT_NAME} PARENT_SCOPE)
    message(STATUS "Bootstrapping EzCMK into ${PROJECT_NAME}")
endfunction()
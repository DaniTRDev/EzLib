add_library("EzLogger"
        "src/Logger.cpp"
        "src/LogSink.cpp"
        "src/EzLogger.cpp"
        "src/Loggers/AsyncLogger.cpp"
        "src/Loggers/SyncLogger.cpp"
        "src/LogMessage/LogMessage.cpp"
        "src/LogMessage/LogSegment.cpp"
        "src/LogSinks/ExceptionSink.cpp"
        "src/LogSinks/WindowsExceptionSink.cpp"
        "src/OutLogBuffers/ConsoleOutLogBuffer.cpp"

        "include/Logger.h"
        "include/EzLogger.h"
        "include/ILogger.h"
        "include/IOutLogBuffer.h"
        "include/ILogSink.h"
        "include/LogSink.h"
        "include/Loggers/AsyncLogger.h"
        "include/Loggers/SyncLogger.h"
        "include/LogMessage/LogMessage.h"
        "include/LogMessage/LogSegment.h"
        "include/LogSinks/ExceptionSink.h"
        "include/LogSinks/WindowsExceptionSink.h"
        "include/OutLogBuffers/ConsoleOutLogBuffer.h"
)

target_include_directories("EzLogger" PUBLIC ${EZLIB_COMMON_PATH})
target_include_directories("EzLogger" PUBLIC "include")

if (EZLIB_BUILD_TESTS)
    message(STATUS "Adding tests for EzLogger")
    add_subdirectory(tests) # Build tests (only if set)
endif ()
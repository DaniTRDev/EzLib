set(EZLOGGER_FILE_LIST
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
        "src/OutLogBuffers/FileOutLogBuffer.cpp"

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
        "include/OutLogBuffers/FileOutLogBuffer.h"
)

EzCMK_ConfigureLib(NAME "EzLogger"
        FILE_LIST ${EZLOGGER_FILE_LIST}
        INCLUDED_DIRS "${EZLIB_COMMON_PATH}" "include"
        PRECOMPILED_HEADER ${EZLIB_COMMON_PATH}/EzLibCommon.h
)

add_subdirectory(tests) # Build tests (only if set)
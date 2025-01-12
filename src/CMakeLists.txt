add_library("EzLogger"
        "Logger.cpp"
        "LogSink.cpp"
        "Loggers/AsyncLogger.cpp"
        "Loggers/SyncLogger.cpp"
        "LogMessage/LogMessage.cpp"
        "LogMessage/LogSegment.cpp"
        "OutLogBuffers/ConsoleOutLogBuffer.cpp"

        "../include/Common.h"
        "../include/Logger.h"
        "../include/EzLogger.h"
        "../include/ILogger.h"
        "../include/IOutLogBuffer.h"
        "../include/LogSink.h"
        "../include/Loggers/AsyncLogger.h"
        "../include/Loggers/SyncLogger.h"
        "../include/LogMessage/LogMessage.h"
        "../include/LogMessage/LogSegment.h"
        "../include/OutLogBuffers/ConsoleOutLogBuffer.h"
)

target_include_directories("EzLogger" PUBLIC "../include")
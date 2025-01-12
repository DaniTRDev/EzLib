#include "Loggers/SyncLogger.h"

bool SyncLogger::pushLog(std::unique_ptr<LogMessage> message)
{
    // Call the super method.
    return Logger::pushLog(std::move(message));
}
std::unique_ptr<LogSink> SyncLogger::createLogSink(const LogSegment &prefix)
{
    return std::make_unique<LogSink>(this, prefix);
}

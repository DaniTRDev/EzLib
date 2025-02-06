#include "Loggers/SyncLogger.h"
#include "Loggers/AsyncLogger.h"

bool SyncLogger::pushLog(std::unique_ptr<LogMessage> message)
{
    // Call the super method.
    return Logger::pushLog(std::move(message));
}

std::unique_ptr<class AsyncLogger> SyncLogger::switchToAsync()
{
    std::unique_ptr<class AsyncLogger> async = std::make_unique<class AsyncLogger>();
    swap(async.get()); // Copy all information to async and clear this.

    return std::move(async);
}

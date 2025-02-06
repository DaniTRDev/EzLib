#ifndef EZLOGGER_SYNCLOGGER_H
#define EZLOGGER_SYNCLOGGER_H

#include "Logger.h"

class SyncLogger : public Logger
{
  public:
    /**
     * Writes the message directly.
     * @param message
     */
    [[nodiscard]] bool pushLog(std::unique_ptr<LogMessage> message) override;
    
    /**
     * Switches this log from Sync to Async. It sets the out buffers of the new logger with the ones in this,
     * same for sinks.
     * @return
     */
    [[nodiscard]] std::unique_ptr<class AsyncLogger> switchToAsync();
};

#endif // EZLOGGER_SYNCLOGGER_H

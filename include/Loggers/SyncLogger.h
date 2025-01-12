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
     * Creates a sink with the given prefix.
     * @param prefix
     * @return std::unique_ptr<class LogSink>
     */
    [[nodiscard]] std::unique_ptr<LogSink> createLogSink(const LogSegment &prefix) override;
};

#endif // EZLOGGER_SYNCLOGGER_H

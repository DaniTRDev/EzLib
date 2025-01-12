#ifndef EZLOGGER_ILOGGER_H
#define EZLOGGER_ILOGGER_H

#include "Common.h"

/**
 * Interface for a Logger. Each logger must contain its own log function and the output buffers pushLog will be written
 * into.
 */
class ILogger
{
  public:
    /**
     * Destroys the object.
     */
    virtual ~ILogger() = default;

    /**
     * Pushes a message to the log. Returns true if succeeded
     * @param message
     * @return bool
     */
    virtual bool pushLog(std::unique_ptr<class LogMessage> message) = 0;

    /**
     * Creates a sink for this logger.
     * @param prefix
     * @return std::unique_ptr<LogSink>
     */
    virtual std::unique_ptr<class LogSink> createLogSink(const class LogSegment &prefix) = 0;
};

#endif // EZLOGGER_ILOGGER_H

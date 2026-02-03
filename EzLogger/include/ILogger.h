#ifndef EZLOGGER_ILOGGER_H
#define EZLOGGER_ILOGGER_H

#include "EzLibCommon.h"

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
    virtual bool pushLog(class LogMessage message) = 0;

    /**
     * Returns true if debug logging is enabled for this logger.
     * @return bool
     */
    virtual bool isDebugLoggingEnabled() = 0;

    /**
     * Enables debug logging.
     */
    virtual void enableDebugLogging() = 0;

  protected:
    std::vector<std::unique_ptr<class IOutLogBuffer>> m_outBuffers;
    // Buffers in which each pushLog message will be written into.
};

#endif // EZLOGGER_ILOGGER_H

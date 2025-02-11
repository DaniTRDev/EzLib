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
     * Logs a message with a DEBUG indication, no sink needed.
     * @param msg
     */
    virtual void logDebug(const class LogMessage &msg) = 0;
    
    /**
     * Logs a message with an INFO indication, no sink needed.
     * @param msg
     */
    virtual void logInfo(const class LogMessage &msg) = 0;
    
    /**
     * Logs a message with a WARNING indication, no sink needed.
     * @param msg
     */
    virtual void logWarn(const class LogMessage &msg) = 0;
    
    /**
     * Logs a message with an ERROR indication, no sink needed.
     * @param msg
     */
    virtual void logError(const class LogMessage &msg) = 0;
    
    /**
     * Pushes a message to the log. Returns true if succeeded
     * @param message
     * @return bool
     */
    virtual bool pushLog(std::unique_ptr<class LogMessage> message) = 0;
    
  protected:
    std::vector<std::unique_ptr<class IOutLogBuffer>> m_outBuffers;
    // Buffers in which each pushLog message will be written into.
};

#endif // EZLOGGER_ILOGGER_H

#ifndef EZLOGGER_ILOGSINK_H
#define EZLOGGER_ILOGSINK_H

#include "EzLibCommon.h"
#include "LogMessage/LogMessage.h"

/**
 * This class represents an interface for a log sink.
 */
class ILogSink
{
  public:
    /**
     * Destroys the object.
     */
    virtual ~ILogSink() = default;
    
    /**
     * Logs a message with a DEBUG indication.
     * @param msg
     */
    virtual void logDebug(LogMessage msg) = 0;
    
    /**
     * Logs a message with an ERROR indication.
     * @param msg
     */
    virtual void logError(LogMessage msg) = 0;
    
    /**
	 * Logs a message with an INFO indication.
	 * @param msg
     */
    virtual void logInfo(LogMessage msg) = 0;
    
    /**
     * Logs a message with a WARNING indication.
     * @param msg
     */
    virtual void logWarn(LogMessage msg) = 0;
    
    /**
     * Pushes a log to the internal logger and returns true if succeeded.
     * @param msg
     * @return bool
     */
    virtual bool pushLog(LogMessage msg) = 0;
    
  protected:
    class ILogger *m_logger{}; // Used by this sink to send the log message.
    class LogSegment m_prefix;
};

#endif // EZLOGGER_ILOGSINK_H

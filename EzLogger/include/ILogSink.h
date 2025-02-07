#ifndef EZLOGGER_ILOGSINK_H
#define EZLOGGER_ILOGSINK_H

#include "EzLibCommon.h"
#include "LogMessage/LogSegment.h"

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
     * Pushes a log to the internal logger and returns true if succeeded.
     * @param msg
     * @return bool
     */
    virtual bool pushLog(const class LogMessage &msg) = 0;
    
  protected:
    class ILogger *m_logger{}; // Used by this sink where to send the log to.
    class LogSegment m_prefix{""};
};

#endif // EZLOGGER_ILOGSINK_H

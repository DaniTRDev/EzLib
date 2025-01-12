#ifndef EZLOGGER_LOGSINK_H
#define EZLOGGER_LOGSINK_H

#include "Common.h"
#include "ILogger.h"
#include "LogMessage/LogMessage.h"

/**
 * Represents a sink of log messages. At the moment sink only sets the prefix of the log messages sent to them. But its
 * functionality might be augmented in a future.
 */
class LogSink
{
  public:
    /**
     * Creates the sink with the given prefix and logger. This object can only be created by Logger.
     * @param prefix
     * @param logger
     */
    LogSink(ILogger *logger, const LogSegment &prefix);

    /**
     * Destroys the object.
     */
    ~LogSink();

    /**
     * Pushes a log to the internal logger and returns true if succeeded.
     * @param msg
     * @return bool
     */
    [[nodiscard]] bool pushLog(const LogMessage &msg) const;

  private:
    ILogger *m_logger; // Used by this sink where to send the log to.
    LogSegment m_prefix;
};

#endif // EZLOGGER_LOGSINK_H

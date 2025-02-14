#ifndef EZLOGGER_LOGSINK_H
#define EZLOGGER_LOGSINK_H

#include "EzLibCommon.h"
#include "LogMessage/LogMessage.h"
#include "ILogSink.h"
#include "ILogger.h"

/**
 * Represents a basic sink of log messages. At the moment sink only sets the prefix of the log messages sent to them. But its
 * functionality might be augmented in a future.
 */
class LogSink : public ILogSink
{
  public:
    /**
     * Creates the sink with the given prefix and logger. This object can only be created by Logger.
     * @param prefix
     * @param logger
     */
    LogSink(ILogger *logger, const LogSegment &prefix);

    /**
     * Defines an explicit copy-constructor.
     * @param copy
     */
    LogSink(const LogSink &copy);
    
    /**
     * Destroys the object.
     */
    ~LogSink() override;

    /**
     * Pushes a log to the internal logger and returns true if succeeded.
     * @param msg
     * @return bool
     */
    bool pushLog(const LogMessage &msg) override;
    
    /**
     * Sets the logger for this class.
     * @param logger
     */
    void setLogger(class ILogger* logger);

  private:
    std::mutex m_mutex; // Make this class thread-safe by default.
};

#endif // EZLOGGER_LOGSINK_H

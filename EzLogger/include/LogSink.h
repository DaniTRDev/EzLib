#ifndef EZLOGGER_LOGSINK_H
#define EZLOGGER_LOGSINK_H

#include "EzLibCommon.h"
#include "ILogSink.h"
#include "ILogger.h"

/**
 * Represents a basic sink of log messages. If debug messages want to be shown, EZLOGGER_ENABLE_DEBUG_LOG macro should
 * be defined.
 */
class LogSink : public ILogSink
{
  public:
    /**
     * Creates the sink with the given prefix and logger. This object can only be created by Logger.
     * @param prefix
     * @param logger
     */
    LogSink(ILogger *logger, LogSegment prefix);

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
    bool pushLog(LogMessage msg) override;

    /**
     * Logs a message with a DEBUG indication.
     * @param msg
     */
    void logDebug(LogMessage msg) override;

    /**
     * Logs a message with an ERROR indication.
     * @param msg
     */
    void logError(LogMessage msg) override;

    /**
     * Logs a message with an INFO indication.
     * @param msg
     */
    void logInfo(LogMessage msg) override;

    /**
     * Logs a message with a WARNING indication.
     * @param msg
     */
    void logWarn(LogMessage msg) override;

    /**
     * Sets the logger for this class.
     * @param logger
     */
    void setLogger(class ILogger *logger);

  private:
    std::mutex m_mutex; // Make this class thread-safe by default.
};

#endif // EZLOGGER_LOGSINK_H

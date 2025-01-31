#ifndef EZLOGGER_EXCEPTIONLOGGER_H
#define EZLOGGER_EXCEPTIONLOGGER_H

#include "LogSink.h"

class ExceptionLogger : public LogSink
{
  public:
    /**
     * Creates the sink.
     * @param logger
     * @param prefix
     */
    ExceptionLogger(ILogger *logger, const LogSegment &prefix);

    /**
     * Destroys the object.
     */
    ~ExceptionLogger();

    /**
     * Attaches a signal logger to the current THREAD. IMPORTANT NOTE: If a thread calls attachSignalLogger,
     * detachSignalLogger must be also called by this thread. If it is not called during the life of the object,
     * destructor will attempt to call it, ensure that the thread calling the destructor is the same thread.
     */
    void attachSignalLogger();

    /**
     * Attaches a signal a VEH and an UEF to log exceptions. Linked to the current PROCESS.
     */
    void attachWindowsLogger();

    /**
     * Tries to detach signal loggers for this thread.
     */
    void detachSignalLogger();

    /**
     * Detaches the VEH and UEF logger.
     */
    void detachWindowsLogger();

  private:
    /**
     * Handler used to catch exceptions in a WINDOWS process.
     * @param ex
     * @return LONG
     */
    static LONG InternalExceptionLogger(EXCEPTION_POINTERS *ex);

  private:
    bool m_attachedSignalHandler;
    static LogSink *m_internalExceptionLoggerSink;
    void *m_previousUefHandler;
    void *m_vehHandler;
};

#define EZLOGGER_LOG_TRY_CATCH(sink, code)                                                                             \
    try                                                                                                                \
    {                                                                                                                  \
        code                                                                                                           \
    }                                                                                                                  \
    catch (std::exception & ex)                                                                                        \
    {                                                                                                                  \
        LogMessage msg = LogMessage("");                                                                               \
        msg.append(LogSegment("WARNING:").colorize(Colors::yellow));                                                   \
        msg.append(LogSegment(" Received C/C++ exception: {}", ex.what()));                                            \
        sink->pushLog(msg);                                                                                            \
    }

#endif // EZLOGGER_EXCEPTIONLOGGER_H

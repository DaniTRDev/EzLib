#ifndef EZLOGGER_WINDOWSEXCEPTIONSINK_H
#define EZLOGGER_WINDOWSEXCEPTIONSINK_H

#include "Common.h"
#include "ExceptionSink.h"

#ifdef EZLIB_WORKING_WINDOWS

class WindowsExceptionSink : public ExceptionSink
{
  public:
    /**
     * Creates the sink.
     * @param logger
     * @param prefix
     */
    WindowsExceptionSink(ILogger *logger, const LogSegment &prefix);

    /**
     * Destroys the obj.
     */
    ~WindowsExceptionSink();

    /**
     * Attaches a signal a VEH and an UEF to log exceptions. Linked to the current PROCESS.
     */
    void attachWindowsLogger();

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
    static LogSink *m_internalExceptionLoggerSink;
    void *m_previousUefHandler;
    void *m_vehHandler;
};

#endif

#endif // EZLOGGER_WINDOWSEXCEPTIONSINK_H

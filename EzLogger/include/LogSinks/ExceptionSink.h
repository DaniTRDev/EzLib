#ifndef EZLOGGER_EXCEPTIONSINK_H
#define EZLOGGER_EXCEPTIONSINK_H

#include "LogSink.h"

class ExceptionSink : public LogSink
{
public:
	/**
	 * Creates the sink.
	 * @param logger
	 * @param prefix
	 */
	ExceptionSink(ILogger *logger, const LogSegment &prefix);

	/**
	 * Destroys the object.
	 */
	~ExceptionSink();

	/**
	 * Attaches a signal logger to the current THREAD. IMPORTANT NOTE: If a thread calls attachSignalLogger,
	 * detachSignalLogger must be also called by this thread. If it is not called during the life of the object,
	 * destructor will attempt to call it, ensure that the thread calling the destructor is the same thread.
	 */
	void attachSignalLogger();

	/**
	 * Tries to detach signal loggers for this thread.
	 */
	void detachSignalLogger();

private:
	bool m_attachedSignalHandler;
};

#define EZLOGGER_LOG_TRY_CATCH(sink, code)                                                                             \
    try                                                                                                                \
    {                                                                                                                  \
        code                                                                                                           \
    }                                                                                                                  \
    catch (std::exception & ex)                                                                                        \
    {                                                                                                                  \
        LogMessage msg = LogMessage("");                                                                               \
        msg.add("WARNING: ").colorize(Colors::yellow);                                                                 \
        msg.add("Received C/C++ exception: {}", ex.what());                                                            \
        sink->pushLog(msg);                                                                                            \
    }

#endif // EZLOGGER_EXCEPTIONSINK_H

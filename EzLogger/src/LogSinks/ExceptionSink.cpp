#include "LogSinks/ExceptionSink.h"

ExceptionSink::ExceptionSink(ILogger *logger, const LogSegment &prefix)
		: m_attachedSignalHandler(false), LogSink(logger, prefix)
{
}

ExceptionSink::~ExceptionSink()
{
	this->pushLog(LogMessage("").add("Shutting down sink:").add(m_prefix.getText()));
	detachSignalLogger();

    LogSink::~ILogSink();
}

void ExceptionSink::attachSignalLogger()
{
	static std::map<int32_t, const char *> signalToStr = {{ SIGABRT, "SIGABRT" },
														  { SIGFPE,  "SIGFPE" },
														  { SIGILL,  "SIGILL" },
														  { SIGINT,  "SIGINT" },
														  { SIGSEGV, "SIGSEV" },
														  { SIGTERM, "SIGTERM" }};

	static std::map<uint64_t, LogSink *> threadSinks; // Map used to save the corresponding sink for the calling thread.

	static auto signalLogger = [](int sig)
	{
		uint64_t threadId = OsDependant::GetThreadId();
		LogMessage msg = LogMessage("");
		msg.add("ERROR: ").colorize(Colors::red);
		msg.add("Received signal: ");
		msg.add("{} ", signalToStr[ sig ]).colorize(Colors::red);
		msg.add("from thread: ");
		msg.add("0x{:X}", threadId).colorize(Colors::blue);

		if (!threadSinks.contains(threadId))
		{
			throw std::runtime_error(
					std::format("Exception sink for signal handler (linked to: thread 0x{:X}) is not attached!",
								threadId));
		}

		threadSinks[ threadId ]->pushLog(msg);
	};

	std::signal(SIGABRT, signalLogger);
	std::signal(SIGFPE, signalLogger);
	std::signal(SIGILL, signalLogger);
	std::signal(SIGINT, signalLogger);
	std::signal(SIGSEGV, signalLogger);
	std::signal(SIGTERM, signalLogger);

	threadSinks.insert({ OsDependant::GetThreadId(), this });
	m_attachedSignalHandler = true;
}

void ExceptionSink::detachSignalLogger()
{
	if (m_attachedSignalHandler)
	{
		std::signal(SIGABRT, SIG_DFL);
		std::signal(SIGFPE, SIG_DFL);
		std::signal(SIGILL, SIG_DFL);
		std::signal(SIGINT, SIG_DFL);
		std::signal(SIGSEGV, SIG_DFL);
		std::signal(SIGTERM, SIG_DFL);
	}
}
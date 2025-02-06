#include "LogSinks/ExceptionSink.h"

ExceptionSink::ExceptionSink(ILogger *logger, const LogSegment &prefix)
    : m_attachedSignalHandler(false), LogSink(logger, prefix)
{
}

ExceptionSink::~ExceptionSink()
{
    this->pushLog(LogMessage("Shutting down sink: ").append(m_prefix));
    detachSignalLogger();
}

void ExceptionSink::attachSignalLogger()
{
    static std::map<int32_t, const char *> signalToStr = {{SIGABRT, "SIGABRT"}, {SIGFPE, "SIGFPE"},
                                                          {SIGILL, "SIGILL"},   {SIGINT, "SIGINT"},
                                                          {SIGSEGV, "SIGSEV"},  {SIGTERM, "SIGTERM"}};

    static std::map<uint64_t, LogSink *> threadSinks; // Map used to save the corresponding sink for the calling thread.

    auto signalLogger = [](int sig) {
        uint64_t threadId = GetCurrentThreadId();
        LogMessage msg = LogMessage("");
        msg.append(LogSegment("ERROR: ").colorize(Colors::red));
        msg.append(LogSegment("Received signal: "));
        msg.append(LogSegment("{} ", signalToStr[sig]).colorize(Colors::red));
        msg.append(LogSegment("from thread: "));
        msg.append(LogSegment("0x{:X}", threadId).colorize(Colors::blue));

        if (!threadSinks.contains(threadId))
        {
            throw std::runtime_error(
                std::format("Exception sink for signal handler (linked to: thread 0x{:X}) is not attached!", threadId));
        }

        threadSinks[threadId]->pushLog(msg);
    };

    std::signal(SIGABRT, signalLogger);
    std::signal(SIGFPE, signalLogger);
    std::signal(SIGILL, signalLogger);
    std::signal(SIGINT, signalLogger);
    std::signal(SIGSEGV, signalLogger);
    std::signal(SIGTERM, signalLogger);

    threadSinks.insert({GetCurrentThreadId(), this});
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
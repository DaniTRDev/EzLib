#include "LogSinks/ExceptionLogger.h"

LogSink *ExceptionLogger::m_internalExceptionLoggerSink = nullptr;

ExceptionLogger::ExceptionLogger(ILogger *logger, const LogSegment &prefix)
    : m_attachedSignalHandler(false), m_previousUefHandler(nullptr), m_vehHandler(nullptr), LogSink(logger, prefix)
{
}

ExceptionLogger::~ExceptionLogger()
{
    this->pushLog(LogMessage("Shutting down sink: ").append(m_prefix));

    detachSignalLogger();
    detachWindowsLogger();
}

void ExceptionLogger::attachSignalLogger()
{
    static std::map<int32_t, const char *> signalToStr = {{SIGABRT, "SIGABRT"}, {SIGFPE, "SIGFPE"},
                                                          {SIGILL, "SIGILL"},   {SIGINT, "SIGINT"},
                                                          {SIGSEGV, "SIGSEV"},  {SIGTERM, "SIGTERM"}};

    static std::map<uint64_t, LogSink *> threadSinks; // Map used to save the corresponding sink for the calling thread.

    static auto signalLogger = [](int sig) {
        uint64_t threadId = GetCurrentThreadId();
        LogMessage msg = LogMessage("");
        msg.append(LogSegment("Warning:").colorize(Colors::yellow));
        msg.append(LogSegment("Received signal: "));
        msg.append(LogSegment("{}", signalToStr[sig]).colorize(Colors::red));
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

    m_attachedSignalHandler = true;
}

void ExceptionLogger::attachWindowsLogger()
{
    if (m_internalExceptionLoggerSink)
    {
        this->pushLog(LogMessage("Sink: ").append(m_prefix).append(
            " tried to attach a VEH and an UEF logger and there's one already"));
        return;
    }

    m_internalExceptionLoggerSink = this;

    m_vehHandler =
        AddVectoredContinueHandler(1, (PVECTORED_EXCEPTION_HANDLER)&ExceptionLogger::InternalExceptionLogger);

    m_previousUefHandler =
        (void *)SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)&ExceptionLogger::InternalExceptionLogger);
}

void ExceptionLogger::detachSignalLogger()
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

void ExceptionLogger::detachWindowsLogger()
{
    if (m_previousUefHandler && m_vehHandler)
    {
        RemoveVectoredContinueHandler(m_vehHandler);
        SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)m_previousUefHandler);
        
        m_internalExceptionLoggerSink = nullptr;
    }
}

LONG ExceptionLogger::InternalExceptionLogger(EXCEPTION_POINTERS *ex)
{
    static std::map<DWORD, const char *> exceptionToStr = {
        {EXCEPTION_ACCESS_VIOLATION, "EXCEPTION_ACCESS_VIOLATION"},
        {EXCEPTION_ARRAY_BOUNDS_EXCEEDED, "EXCEPTION_ARRAY_BOUNDS_EXCEEDED"},
        {EXCEPTION_BREAKPOINT, "EXCEPTION_BREAKPOINT"},
        {EXCEPTION_DATATYPE_MISALIGNMENT, "EXCEPTION_DATATYPE_MISALIGNMENT"},
        {EXCEPTION_FLT_DENORMAL_OPERAND, "EXCEPTION_FLT_DENORMAL_OPERAND"},
        {EXCEPTION_FLT_DIVIDE_BY_ZERO, "EXCEPTION_FLT_DIVIDE_BY_ZERO"},
        {EXCEPTION_FLT_INEXACT_RESULT, "EXCEPTION_FLT_INEXACT_RESULT"},
        {EXCEPTION_FLT_INVALID_OPERATION, "EXCEPTION_FLT_INVALID_OPERATION"},
        {EXCEPTION_FLT_OVERFLOW, "EXCEPTION_FLT_OVERFLOW"},
        {EXCEPTION_FLT_STACK_CHECK, "EXCEPTION_FLT_STACK_CHECK"},
        {EXCEPTION_FLT_UNDERFLOW, "EXCEPTION_FLT_UNDERFLOW"},
        {EXCEPTION_ILLEGAL_INSTRUCTION, "EXCEPTION_ILLEGAL_INSTRUCTION"},
        {EXCEPTION_IN_PAGE_ERROR, "EXCEPTION_IN_PAGE_ERROR"},
        {EXCEPTION_INT_DIVIDE_BY_ZERO, "EXCEPTION_INT_DIVIDE_BY_ZERO"},
        {EXCEPTION_INT_OVERFLOW, "EXCEPTION_INT_OVERFLOW"},
        {EXCEPTION_INVALID_DISPOSITION, "EXCEPTION_INVALID_DISPOSITION"},
        {EXCEPTION_NONCONTINUABLE_EXCEPTION, "EXCEPTION_NONCONTINUABLE_EXCEPTION"},
        {EXCEPTION_PRIV_INSTRUCTION, "EXCEPTION_PRIV_INSTRUCTION"},
        {EXCEPTION_SINGLE_STEP, "EXCEPTION_SINGLE_STEP"},
        {EXCEPTION_STACK_OVERFLOW, "EXCEPTION_STACK_OVERFLOW"},
        {DBG_CONTROL_C, "DBG_CONTROL_C "}

    };

    LogMessage msg = LogMessage("");
    msg.append(LogSegment("ERROR:").colorize(Colors::red));
    msg.append(LogSegment("Received exception: "));
    msg.append(LogSegment("{}", exceptionToStr[ex->ExceptionRecord->ExceptionCode]).colorize(Colors::red));
    msg.append(LogSegment("at: "));
    msg.append(LogSegment("0x{:X}", ex->ExceptionRecord->ExceptionAddress).colorize(Colors::blue));

    if (!ExceptionLogger::m_internalExceptionLoggerSink)
    {
        throw std::runtime_error("Sink for exception logger is not alive!");
    }

    ExceptionLogger::m_internalExceptionLoggerSink->pushLog(msg);

    return EXCEPTION_CONTINUE_SEARCH;
}

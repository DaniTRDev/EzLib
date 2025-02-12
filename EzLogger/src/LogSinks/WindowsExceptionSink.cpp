#include "LogSinks/WindowsExceptionSink.h"

#ifdef EZLIB_WORKING_WINDOWS

LogSink *WindowsExceptionSink::m_internalExceptionLoggerSink = nullptr;

WindowsExceptionSink::WindowsExceptionSink(ILogger *logger, const LogSegment &prefix)
    : m_previousUefHandler(nullptr), m_vehHandler(nullptr), ExceptionSink(logger, prefix)
{
}

WindowsExceptionSink::~WindowsExceptionSink()
{
    detachWindowsLogger();
}

void WindowsExceptionSink::attachWindowsLogger()
{
    if (m_internalExceptionLoggerSink)
    {
        this->pushLog(LogMessage("")
                          .add("Sink: ")
                          .add(m_prefix.getText())
                          .add(" tried to attach a VEH and an UEF logger and there's one already"));
        return;
    }

    m_internalExceptionLoggerSink = this;

    m_vehHandler =
        AddVectoredContinueHandler(1, (PVECTORED_EXCEPTION_HANDLER)&WindowsExceptionSink::InternalExceptionLogger);

    m_previousUefHandler = (void *)SetUnhandledExceptionFilter(
        (LPTOP_LEVEL_EXCEPTION_FILTER)&WindowsExceptionSink::InternalExceptionLogger);
}

void WindowsExceptionSink::detachWindowsLogger()
{
    if (m_previousUefHandler && m_vehHandler)
    {
        RemoveVectoredContinueHandler(m_vehHandler);
        SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)m_previousUefHandler);

        m_internalExceptionLoggerSink = nullptr;
    }
}
LONG WindowsExceptionSink::InternalExceptionLogger(EXCEPTION_POINTERS *ex)
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
    msg.add("ERROR: ").colorize(Colors::red);
    msg.add("Received exception: ");
    msg.add("{} ", exceptionToStr[ex->ExceptionRecord->ExceptionCode]).colorize(Colors::red);
    msg.add("at: ");
    msg.add("0x{:X}", size_t(ex->ExceptionRecord->ExceptionAddress)).colorize(Colors::blue);

    if (!m_internalExceptionLoggerSink)
    {
        throw std::runtime_error("Sink for exception logger is not alive!");
    }

    m_internalExceptionLoggerSink->pushLog(msg);

    return EXCEPTION_CONTINUE_SEARCH;
}

#endif
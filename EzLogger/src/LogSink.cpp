#include "LogSink.h"

LogSink::LogSink(ILogger *logger, LogSegment prefix)
{
    // Set protected members of ILogSink.
    this->m_logger = logger;
    this->m_prefix = std::move(prefix);
}

LogSink::LogSink(const LogSink &copy)
{
    // Set protected members of ILogSink.
    this->m_logger = copy.m_logger;
    this->m_prefix = copy.m_prefix;
}

LogSink::~LogSink()
{
    m_logger = nullptr;
    m_prefix = LogSegment("");
}

bool LogSink::pushLog(LogMessage msg)
{
    std::scoped_lock lock(m_mutex);

    if (!m_logger)
        return false;
    
    msg.setPrefix(m_prefix);
    return m_logger->pushLog(std::move(msg));
}

void LogSink::setLogger(ILogger *logger)
{
    m_logger = logger;
}

void LogSink::logDebug(LogMessage msg)
{
    msg.setPrefix(std::move(LogSegment("DEBUG").colorize(Colors::blue)));
    pushLog(std::move(msg));
}

void LogSink::logError(LogMessage msg)
{
    msg.setPrefix(std::move(LogSegment("ERROR").colorize(Colors::red)));
    pushLog(std::move(msg));
}

void LogSink::logInfo(LogMessage msg)
{
    msg.setPrefix(std::move(LogSegment("DEBUG").colorize(Colors::cyan)));
    pushLog(std::move(msg));
}

void LogSink::logWarn(LogMessage msg)
{
    msg.setPrefix(std::move(LogSegment("DEBUG").colorize(Colors::yellow)));
    pushLog(std::move(msg));
}

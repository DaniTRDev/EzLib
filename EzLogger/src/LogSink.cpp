#include "LogSink.h"

LogSink::LogSink(ILogger *logger, const LogSegment &prefix)
{
    // Set protected members of ILogSink.
    this->m_logger = logger;
    this->m_prefix = prefix;
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

bool LogSink::pushLog(const LogMessage &msg)
{
    std::scoped_lock lock(m_mutex);

    if (!m_logger)
        return false;

    std::unique_ptr<LogMessage> copy = std::make_unique<LogMessage>(msg);
    copy->setPrefix(m_prefix);

    return m_logger->pushLog(std::move(copy));
}

void LogSink::setLogger(ILogger *logger)
{
    m_logger = logger;
}

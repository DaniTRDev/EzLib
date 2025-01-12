#include "LogSink.h"

LogSink::LogSink(ILogger *logger, const LogSegment &prefix) : m_logger(logger), m_prefix(prefix)
{
}

LogSink::~LogSink()
{
    m_logger = nullptr;
}

bool LogSink::pushLog(const LogMessage &msg) const
{
    if (!m_logger)
        return false;

    std::unique_ptr<LogMessage> copy = std::make_unique<LogMessage>(msg);
    copy->setPrefix(m_prefix);

    return m_logger->pushLog(std::move(copy));
}

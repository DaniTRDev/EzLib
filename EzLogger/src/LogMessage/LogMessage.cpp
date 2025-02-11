#include "LogMessage/LogMessage.h"
// #include "include/LogSink.h"

LogMessage::LogMessage(const LogSegment &prefix) : m_prefix(prefix)
{}

LogMessage::~LogMessage()
{
	m_prefix = {""};
    m_segments.clear();
}

LogMessage &LogMessage::add(const std::string &content)
{
	m_segments.push_back(LogSegment(content));
	return *this;
}

std::string LogMessage::getColouredMessage() const
{
    auto prefixStr = m_prefix.getColorized();
    std::string result;

    if (!prefixStr.empty())
    {
        // LogMessage has a prefix, include it.
        result += std::format("[{}] -> ", prefixStr);
    }

    for (auto &segment : m_segments)
    {
        // Append the segment with its color.
        result += std::format("{}", segment.getColorized());
    }

    return std::move(result); // Avoid unnecessary copies.
}

std::string LogMessage::getRawMessage() const
{
    auto prefixStr = m_prefix.getText();
    std::string result;

    if (!prefixStr.empty())
    {
        // LogMessage has a prefix, include it.
        result += std::format("[{}] -> ", prefixStr);
    }

    for (auto &segment : m_segments)
    {
        // Append the segment with its color and ensure the text after it is not colored.
        result += std::format("{}", segment.getText());
    }

    return std::move(result); // Avoid unnecessary copies.
}

void LogMessage::setPrefix(const LogSegment &prefix)
{
    m_prefix = prefix;
}

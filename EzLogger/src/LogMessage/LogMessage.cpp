#include "LogMessage/LogMessage.h"

LogMessage::LogMessage(const std::string &msg)
{
    add(msg);
}

LogMessage::LogMessage() : m_prefix()
{
}

LogMessage::~LogMessage()
{
    m_prefix = {};
    m_segments.clear();
}

LogMessage &LogMessage::add(LogMessage &other)
{
    std::copy(other.m_segments.begin(), other.m_segments.end(), std::back_inserter(m_segments));
    return *this;
}

LogMessage &LogMessage::add(const std::string &content)
{
    m_segments.push_back(LogSegment(content));
    return *this;
}

LogMessage &LogMessage::setPrefix(LogSegment prefix)
{
    if (m_prefix.isInitialized())
    {
        m_segments.insert(m_segments.begin(), std::move(m_prefix)); // Move the old prefix to the message itself.
    }

    m_prefix = std::move(prefix);
    return *this;
}

void LogMessage::moveTo(LogMessage &other)
{
    other.m_prefix = std::move(other.m_prefix);
    other.m_segments = std::move(m_segments);
}

std::string LogMessage::getColouredMessage() const
{
    auto prefixStr = m_prefix.getColorized();
    std::string result;

    if (!prefixStr.empty())
    {
        // LogMessage has a prefix, include it.
        result += std::format("[{}] ", prefixStr);
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
        result += std::format("[{}]  ", prefixStr);
    }

    for (auto &segment : m_segments)
    {
        // Append the segment with its color and ensure the text after it is not colored.
        result += std::format("{}", segment.getText());
    }

    return std::move(result); // Avoid unnecessary copies.
}

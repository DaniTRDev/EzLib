#include "LogMessage/LogSegment.h"

LogSegment::LogSegment(const std::string &text) : m_text(text)
{
}

LogSegment::~LogSegment()
{
    m_text.clear();
    m_text = "";
}

std::string LogSegment::getColorized() const
{
    if (m_text.empty())
        return ""; // Do not make std::format work if the text is empty, why would we want an empty colored string?

    std::string result;
    for (auto &color : m_colors)
    {
        result += std::format("{}", color);
    }

    result += m_text + std::format("{}", Colors::reset);
    return result;
}

const std::string &LogSegment::getText() const
{
    return m_text;
}

const std::vector<SimpleColor> &LogSegment::getColors() const
{
    return m_colors;
}

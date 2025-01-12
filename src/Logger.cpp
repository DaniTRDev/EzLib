#include "Logger.h"

std::unique_ptr<LogSink> Logger::createSink(const LogSegment &prefix)
{
    return std::make_unique<LogSink>(this, prefix);
}

bool Logger::pushLog(std::unique_ptr<LogMessage> message)
{
    bool result = true;

    for (auto &buffer : m_outBuffers)
    {
        if (!buffer->opened())
        {
            if (!buffer->open())
                throw std::runtime_error("Could not open out buffer!");
        }

        result &= buffer->write(message);
    }

    return result;
}

void Logger::addBuffer(std::unique_ptr<IOutLogBuffer> buffer)
{
    m_outBuffers.push_back(std::move(buffer));
}

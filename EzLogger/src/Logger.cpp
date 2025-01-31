#include "Logger.h"

Logger::~Logger()
{
    m_sinks.clear();
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

const std::vector<std::shared_ptr<LogSink>> &Logger::getSinks() const
{
    return m_sinks;
}

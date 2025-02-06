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

void Logger::swap(Logger *destination)
{
    std::vector<std::shared_ptr<LogSink>> copySinks = destination->getSinks();
    std::vector<std::unique_ptr<IOutLogBuffer>> copyBuff = std::move(destination->m_outBuffers);
    
    
    for(auto &copySink : copySinks)
    {
        // Update logger for destination sinks.
        copySink->setLogger(this);
    }
    
    for(auto &sink : getSinks())
    {
        // Update logger for our own sinks.
        sink->setLogger(destination);
    }
    
    destination->m_sinks = m_sinks;
    destination->m_outBuffers = std::move(m_outBuffers);
    
    m_sinks = copySinks;
    m_outBuffers = std::move(copyBuff);
}

const std::vector<std::shared_ptr<LogSink>> &Logger::getSinks() const
{
    return m_sinks;
}

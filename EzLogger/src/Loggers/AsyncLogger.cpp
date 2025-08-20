#include "Loggers/AsyncLogger.h"

AsyncLogger::AsyncLogger() : m_isInternalThreadAlive(false), m_working(true)
{
}

AsyncLogger::~AsyncLogger()
{
    m_working = false;

    if (m_isInternalThreadAlive)
        m_thread.join();

    while (!m_messages.empty())
        m_messages.pop();
}

bool AsyncLogger::isInternalThreadAlive() const
{
    return m_isInternalThreadAlive;
}

bool AsyncLogger::isWorking() const
{
    return m_working;
}

bool AsyncLogger::killThread()
{
    if (!m_isInternalThreadAlive)
        return true;

    setWorking(false); // Stop working to kill the thread.
    m_thread.join();   // Wait until thread finishes executing.
    setWorking(true);  // Resume work.

    return !m_isInternalThreadAlive;
}

bool AsyncLogger::log(AsyncLogger *logger)
{
    std::scoped_lock lock(logger->m_mutex); // Locks mutex.

    if (!logger->isWorking() || !logger->areThereMessages())
        return true;

    return logger->Logger::pushLog(std::move(logger->getFirstMessage()));
}

bool AsyncLogger::pushLog(LogMessage message)
{
    std::scoped_lock lock(m_mutex);
    m_messages.push(std::move(message));

    return true;
}

void AsyncLogger::spawnThread()
{
    std::unique_lock lock(m_mutex);

    if (m_isInternalThreadAlive)
        return; // Only allow 1 instance of the thread to be created.

    static auto threadFunc = [](AsyncLogger *logger) {
        logger->m_isInternalThreadAlive = true;
        while (logger->m_working)
        {
            if (!AsyncLogger::log(logger))
                throw std::runtime_error("Logger thread couldn't log a message!");

            std::this_thread::yield();
        }
        logger->m_isInternalThreadAlive = false;
    };

    lock.unlock(); // Unlock the mutex so the newly created thread can use it.

    m_thread = std::thread(threadFunc, this);
}

void AsyncLogger::setWorking(bool state)
{
    m_working = state;
}

bool AsyncLogger::areThereMessages()
{
    return !m_messages.empty();
}

LogMessage AsyncLogger::getFirstMessage()
{
    LogMessage result;
    m_messages.front().moveTo(result);
    m_messages.pop();
    return std::move(result);
}

#include "Loggers/AsyncLogger.h"

AsyncLogger::AsyncLogger() : m_isInternalThreadAlive(false), m_working(true)
{
}

AsyncLogger::~AsyncLogger()
{
    m_working = false;
    
    if (m_isInternalThreadAlive)
        m_thread.join();

    m_outBuffers.clear();
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
    std::scoped_lock lock(m_mutex);

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

    if (!logger->isWorking())
        return true;

    // If queue is empty, the check will fail and the for will not be executed.
    bool result = true;
    if (std::unique_ptr<LogMessage> message = logger->getFirstMessage(); message != nullptr)
        result = logger->Logger::pushLog(std::move(message)); // Call the super method.

    return result;
}

bool AsyncLogger::pushLog(std::unique_ptr<LogMessage> message)
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

std::unique_ptr<LogMessage> AsyncLogger::getFirstMessage()
{
    if (m_messages.empty())
        return nullptr;

    std::unique_ptr<LogMessage> result = std::move(m_messages.front());
    m_messages.pop();

    return result;
}

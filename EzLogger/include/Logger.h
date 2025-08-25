#ifndef EZLOGGER_LOGGER_H
#define EZLOGGER_LOGGER_H

#include "ILogger.h"
#include "IOutLogBuffer.h"
#include "LogMessage/LogMessage.h"
#include "LogSink.h"

/**
 * A class Logger that defines the log method for the ILogger interface. This will log to our own IOutLogBuffer(s).
 *
 * Although this logger is not async, a mutex is needed to ensure that if different threads call pushLog there won't
 * be any error because of shared execution.
 */
class Logger : public ILogger
{
  public:
    
    /**
     * Destroys the object.
     */
    ~Logger();

    /**
     * Sends the log to the out buffers. If a write to any of the buffers fail, function will return false. Writing
     * WON'T be stopped if any of the buffers threw an error because they SHOULD be independent. If a buffer is not
     * opened, this instance will try to open it.
     * @param message
     * @return bool
     */
    bool pushLog(LogMessage message) override;

    /**
     * Adds the buffer to the out buffer list.
     * @param buffer
     */
    void addBuffer(std::unique_ptr<IOutLogBuffer> buffer);
    
    /**
     * Swaps this->m_sinks and out buffer with destination. Can be used to clear sinks and logger if called
     * with an empty vector (Not recommended...).
     * @param destination
     */
    void swap(Logger *destination);
    
    /**
     * Creates a sink of given type with given arguments. This might be converted into a "SinkFactory" in a future.
     * IMPORTANT: An ILogger pointer is passed as the FIRST parameter.
     * @tparam LogSinkT
     * @tparam SinkArgs
     * @param args
     * @return std::shared_ptr<LogSinkT>
     */
    template <typename LogSinkT, typename... SinkArgs>
        requires std::is_base_of_v<LogSink, LogSinkT>
    [[nodiscard]] std::shared_ptr<LogSinkT> createSink(SinkArgs &&...args)
    {
        std::scoped_lock lock(m_mutex);
        m_sinks.emplace_back(this, std::forward<SinkArgs>(args)...);
        return *(m_sinks.end() - 1);
    }
    
    /**
     * Returns the vector of created sinks for this logger.
     * @return const std::vector<std::shared_ptr<LogSink>> &
     */
    [[nodiscard]] const std::vector<std::shared_ptr<LogSink>> &getSinks() const;
    
  private:
    std::mutex m_mutex;
    std::vector<std::shared_ptr<LogSink>> m_sinks;
};

#endif // EZLOGGER_LOGGER_H

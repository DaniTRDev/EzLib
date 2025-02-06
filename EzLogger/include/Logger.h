#ifndef EZLOGGER_LOGGER_H
#define EZLOGGER_LOGGER_H

#include "ILogger.h"
#include "IOutLogBuffer.h"
#include "LogMessage/LogMessage.h"
#include "LogSink.h"

/**
 * A class Logger that defines the log method for the ILogger interface. This will log to our own IOutLogBuffer(s).
 */
class Logger : public ILogger
{
  public:
    
    /**
     * Destroys the object.
     */
    ~Logger();
    
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
        std::shared_ptr<LogSinkT> ptr = std::make_shared<LogSinkT>(this, std::forward<SinkArgs>(args)...);
        m_sinks.push_back(ptr);
        return ptr;
    }

    /**
     * Sends the log to the out buffers. If a write to any of the buffers fail, function will return false. Writing
     * WON'T be stopped if any of the buffers threw an error because they SHOULD be independent. If a buffer is not
     * opened, this instance will try to open it.
     * @param message
     * @return bool
     */
    [[nodiscard]] bool pushLog(std::unique_ptr<LogMessage> message) override;

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
     * Returns the vector of created sinks for this logger.
     * @return const std::vector<std::shared_ptr<LogSink>> &
     */
    [[nodiscard]] const std::vector<std::shared_ptr<LogSink>> &getSinks() const;
    
  private:
    std::vector<std::shared_ptr<LogSink>> m_sinks;
};

#endif // EZLOGGER_LOGGER_H

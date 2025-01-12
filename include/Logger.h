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
     * Creates a sink with the given prefix and returns != nullptr if succeeded.
     * @param prefix
     * @return std::unique_ptr<LogSink>
     */
    [[nodiscard]] std::unique_ptr<LogSink> createSink(const LogSegment &prefix);

    /**
     * Sends the log to the out buffers. If a write to any of the buffers fail, function will return false. Writing
     * WON'T be stopped if any of the buffers threw an error because they SHOULD be independent. If a buffer is not
     * opened, this instance will try to open it.
     * @param message
     * @return
     */
    [[nodiscard]] bool pushLog(std::unique_ptr<LogMessage> message) override;

    /**
     * Adds the buffer to the out buffer list.
     * @param buffer
     */
    void addBuffer(std::unique_ptr<IOutLogBuffer> buffer);

  protected:
    std::vector<std::unique_ptr<IOutLogBuffer>> m_outBuffers;
    // Buffers in which each pushLog message will be written into.
};

#endif // EZLOGGER_LOGGER_H

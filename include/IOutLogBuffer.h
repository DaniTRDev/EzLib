#ifndef EZLOGGER_IOUTLOGBUFFER_H
#define EZLOGGER_IOUTLOGBUFFER_H

#include "Common.h"
#include "LogMessage/LogMessage.h"

/**
 * Interface that represents an output buffer for a log. Each out buffer contains:
 *  - Open / Close method to open and close the internal buffer.
 *  - Write method that will write the log message into the internal output buffer.
 * This interface abstract and encapsulates writing a log message to somewhere.
 */
class IOutLogBuffer
{
  public:
    /**
     * Destroys the object.
     */
    virtual ~IOutLogBuffer() = default;

    /**
     * Closes the internal buffer. Returns true if succeeded.
     * @return bool
     */
    [[nodiscard]] virtual bool close() = 0;

    /**
     * Opens the internal buffer. Returns true if succeeded.
     * @return bool
     */
    [[nodiscard]] virtual bool open() = 0;

    /**
     * Returns true if the internal buffer is opened.
     * @return bool
     */
    [[nodiscard]] virtual bool opened() const = 0;

    /**
     * Writes the log message to the out buffer.
     * @param message
     */
    [[nodiscard]] virtual bool write(const std::unique_ptr<LogMessage> &message) = 0;
};

#endif // EZLOGGER_IOUTLOGBUFFER_H

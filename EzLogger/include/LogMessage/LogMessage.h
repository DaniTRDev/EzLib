#ifndef EZLOGGER_LOGMESSAGE_H
#define EZLOGGER_LOGMESSAGE_H

#include "EzLibCommon.h"
#include "LogSegment.h"

/**
 * This class represents a log factory. It creates a log message, with colors and with a prefix (if set explicitly).
 */
class LogMessage
{
  public:
    /**
     * Creates an empty LogMessage.
     */
    LogMessage();

    /**
     * Creates the message with a non-colored segment.
     * @param msg
     */
    explicit LogMessage(const std::string &msg);

    /**
     * Creates the message with a formated segment.
     * @tparam Args
     * @param fmt
     * @param args
     * @return LogMessage&
     */
    template <typename... Args> explicit inline LogMessage(const char *fmt, Args &&...args)
    {
        add(fmt, std::forward<Args>(args)...);
    }

    /**
     * Destroys this object.
     */
    ~LogMessage();

    /**
     * Adds other's message content into this IGNORING OTHER'S PREFIX. WARNING: This COPIES the content of msg.
     * @param msg
     * @return LogMessage &
     */
    LogMessage &add(LogMessage &other);

    /**
     * Adds a string as a segment and returns the same instance of LogMessage.
     * @return LogMessage&
     */
    LogMessage &add(const std::string &content);

    /**
     * Adds a formated segment to the message and returns the same instance of LogMessage.
     * @tparam Args
     * @param fmt
     * @param args
     * @return LogMessage&
     */
    template <typename... Args> LogMessage &add(const char *fmt, Args &&...args)
    {
        m_segments.push_back(LogSegment(fmt, std::forward<Args>(args)...));
        return *this;
    }

    /**
     * Colors the last segment added. If there are not segments it will do nothing but will return the same instance of
     * LogMessage.
     * @tparam Args
     * @return LogMessage&
     */
    template <typename... Args> LogMessage &colorize(Args &&...args)
    {
        if (!m_segments.empty())
        {
            auto &segment = m_segments.at(m_segments.size() - 1);
            segment.colorize(std::forward<Args>(args)...);
        }

        return *this;
    }

    /**
     * Sets the prefix of the LogMessage. If already set, old will be moved into message's body and
     * new will be set so final message looks like this: [prefix][old prefix] ...
     * @param prefix
     */
    LogMessage &setPrefix(LogSegment prefix);

    /**
     * Moves (not copying) the content of this message to other and LOSES the data in this.
     * @param other
     */
    void moveTo(LogMessage &other);

    /**
     * Returns the coloured string of the message. Avoid unnecessary calls because
     * this method iterates over m_segments and CREATES a string with every segment
     * and its color.
     * @return std::string
     */
    [[nodiscard]] std::string getColouredMessage() const;

    /**
     * Returns the raw message (without colours). Avoid unnecessary calls because
     * this method iterates over m_segments and CREATES a string with every segment.
     * @return std::string
     */
    [[nodiscard]] std::string getRawMessage() const;

  private:
    LogSegment m_prefix;                // what will be printed BEFORE the text on segments.
    std::vector<LogSegment> m_segments; // segments of the message, used to colour.
};

#endif // EZLOGGER_LOGMESSAGE_H

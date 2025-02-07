#ifndef EZLOGGER_LOGMESSAGE_H
#define EZLOGGER_LOGMESSAGE_H

#include "EzLibCommon.h"
#include "LogSegment.h"

/**
 * This class represents a log message. It allows a deeper modification of the pushLog message.
 * For colours, look at LogSegment.
 */
class LogMessage
{
  public:
    /**
     * Creates the object with the given segment.
     * @param segment
     */
    LogMessage(const LogSegment &segment);
    
    /**
     * Destroys this object.
     */
    ~LogMessage();

    /**
     * Appends a segment to the log message and returns a reference to this.
     * @param segment
     * @return LogMessage
     */
    LogMessage &append(const LogSegment &segment);

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

    /**
     * Queues this message for logging at the given sink and sets the prefix of the message.
     * @param worker
     */
    // void log(class LogSink *sink);

    /**
     * Sets the prefix of the LogMessage. If already set, it will be replaced.
     * @param prefix
     */
    void setPrefix(const LogSegment &prefix);

  private:
    LogSegment m_prefix;                // what will be printed BEFORE the text on segments.
    std::vector<LogSegment> m_segments; // segments of the message, used to colour.
};

#endif // EZLOGGER_LOGMESSAGE_H

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
     * Creates the object with the given segment.
     * @param segment
     */
    explicit LogMessage(const LogSegment &prefix);

    /**
     * Destroys this object.
     */
    ~LogMessage();

	/**
	 * Adds a string as a segment and returns the same instance of LogMessage.
	 * @return LogMessage&
	 */
	LogMessage &add(const std::string &content);

    /**
     * Adds a formatted segment to the message and returns the same instance of LogMessage.
     * @tparam Args
     * @param fmt
     * @param args
     * @return LogMessage&
     */
     template<typename ...Args>
    LogMessage &add(const char* fmt, Args&& ...args)
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
	template<typename ...Args>
	LogMessage &colorize(Args&& ...args)
	{
		if (!m_segments.empty())
		{
			auto &segment = m_segments.at(m_segments.size() - 1);
			segment.colorize(std::forward<Args>(args)...);
		}

		return *this;
	}

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
     * Sets the prefix of the LogMessage. If already set, it will be replaced.
     * @param prefix
     */
    void setPrefix(const LogSegment &prefix);

  private:
    LogSegment m_prefix;                // what will be printed BEFORE the text on segments.
    std::vector<LogSegment> m_segments; // segments of the message, used to colour.
};

#endif // EZLOGGER_LOGMESSAGE_H

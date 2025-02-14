#ifndef EZLOGGER_CONSOLEOUTLOGBUFFER_H
#define EZLOGGER_CONSOLEOUTLOGBUFFER_H

#include "IOutLogBuffer.h"

constexpr uint64_t g_maxConsoleTitleLength = 256; // Default for windows.

// TODO: Add availability for other systems such as Unix and Mac.
class ConsoleOutLogBuffer : public IOutLogBuffer
{
  public:
    /**
     * Creates the object. Sets m_consoleHandle to -1 by default. (INVALID_HANDLE_VALUE).
     * @param consoleTitle
     */
    ConsoleOutLogBuffer(std::string_view consoleTitle);

    /**
     * Destroys the object. If console buffer was opened, it will close it.
     */
    ~ConsoleOutLogBuffer() override;

    /**
     * Closes the console buffer and resets console state. Returns true if succeeded.
     * @return bool
     */
    [[nodiscard]] bool close() override;

    /**
     * Opens the console buffer, if console existed, and changes its state to allow colors and allow other features. If
     * console didn't exists it will create a new one. If console existed previously it will save its original state.
     * Returns true if succeeded.
     * @return bool
     */
    [[nodiscard]] bool open() override;

    /**
     * Returns true if console buffer is opened.
     * @return bool
     */
    [[nodiscard]] bool opened() const override;

    /**
     * Writes the log message WITH colors to the out buffer.
     * Returns true if succeeded.
     * @param message
     * @return bool.
     */
    [[nodiscard]] bool write(const std::unique_ptr<LogMessage> &message) override;

  private:
    bool m_didConsoleExist;
    char m_originalConsoleTitle[g_maxConsoleTitleLength];
    uint32_t m_originalConsoleMode;
    uint32_t m_originalConsoleOutput;
    uint64_t m_consoleHandle;
    std::streambuf *m_internalBuffer; // Internal buffer that will write to console.
    std::string_view m_consoleTitle;
};

#endif // EZLOGGER_CONSOLEOUTLOGBUFFER_H

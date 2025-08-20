#ifndef EZLIB_FILEOUTBUFFER_H
#define EZLIB_FILEOUTBUFFER_H

#include "EzLibCommon.h"
#include "IOutLogBuffer.h"

class FileOutLogBuffer : public IOutLogBuffer
{
  public:
    /**
     * Creates the object. Sets m_consoleHandle to -1 by default. (INVALID_HANDLE_VALUE).
     * @param consoleTitle
     */
    FileOutLogBuffer(std::filesystem::path path);
    
    /**
     * Destroys the object. If console buffer was opened, it will close it.
     */
    ~FileOutLogBuffer() override;

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
    [[nodiscard]] bool write(LogMessage message) override;

  private:
    std::filesystem::path m_path;
    std::ofstream m_fileStream;
};

#endif // EZLIB_FILEOUTBUFFER_H

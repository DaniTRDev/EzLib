#ifndef EZLOGGER_ASYNCLOGGER_H
#define EZLOGGER_ASYNCLOGGER_H

#include "Logger.h"

/**
 * A class that represents an asynchronous logger. "Log thread" can be either external (must call AsyncLogger::log)
 * or can be spawned with this class (will spawn a std::thread).
 */
class AsyncLogger : public Logger
{
  public:
    /**
     * Creates the obj. And sets working to true.
     */
    AsyncLogger();

    /**
     * Destroys the object.
     */
    ~AsyncLogger() override;

    /**
     * Returns true if internal thread is alive. False otherways.
     * @return bool
     */
    [[nodiscard]] bool isInternalThreadAlive() const;

    /**
     * Returns true if working.
     * @return bool
     */
    [[nodiscard]] bool isWorking() const;

    /**
     * Tries to kill the thread and WILL BLOCK the calling thread until it dies. Returns true if succeeded.
     * @return bool
     */
    [[nodiscard]] bool killThread();

    /**
     * @PRE Called by the logging thread.
     * Writes the first message of the queue, blocking the mutex, to the out buffers ONLY if working is set to
     * true. Returns true if succeeded and wrote the message, there weren't any messages or working is set to false.
     * @param logger
     * @return bool
     */
    static bool log(AsyncLogger *logger);

    /**
     * Pushes a log message to the queue, the designed thread will write it into the
     * out buffer when it can. Returns true if succeeded.
     * @param message
     * @return bool
     */
    bool pushLog(LogMessage message) override;

    /**
     * Sets the working state of the async logger.
     * @param state
     */
    void setWorking(bool state);

    /**
     * @PRE This instance of the logger will be alive while this thread is alive.
     * Spawns, if possible and not already spawned, an std::thread. If working is set to false, the next time the thread
     * function runs it will exit and kill the thread.
     */
    void spawnThread();
    
  private:
    
    /**
     * Returns true if there are messages in the queue. This function is not thread-safe. It's private for this reason
     * and can only be called by this class on its own
     * @return bool
     */
    [[nodiscard]] bool areThereMessages();
    
    /**
     * Retrieves the first message of the queue (if any) and removes it from the queue.
     * This function is not thread-safe hence why it can only be called by this class on its own.
     * @return std::unique_ptr<LogMessage>
     */
    [[nodiscard]] LogMessage getFirstMessage();

  private:
    bool m_isInternalThreadAlive; // Is m_thread alive?
    bool m_working;               // Bool that will tell the async thread to log or not.
    std::mutex m_mutex;           // Mutex used to control logging.
    std::queue<LogMessage> m_messages;
    std::thread m_thread;
};

#endif // EZLOGGER_ASYNCLOGGER_H

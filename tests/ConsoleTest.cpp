#include "EzLogger.h"
std::shared_ptr<Logger> logger;

void testSync(LogSink *sink)
{
    sink->pushLog(LogMessage(LogSegment("This word should be default")));

    static const std::pair<const char *, const SimpleColor *> colorMap[] = {
        {"bold", &Colors::bold},           {"dim", &Colors::dim},
        {"italic", &Colors::italic},       {"underline", &Colors::underline},
        {"blink", &Colors::blink},         {"reverse", &Colors::reverse},
        {"hidden", &Colors::hidden},       {"strike", &Colors::strike},
        {"black", &Colors::black},         {"red", &Colors::red},
        {"green", &Colors::green},         {"yellow", &Colors::yellow},
        {"blue", &Colors::blue},           {"magenta", &Colors::magenta},
        {"cyan", &Colors::cyan},           {"white", &Colors::white},
        {"brBlack", &Colors::brBlack},     {"brRed", &Colors::brRed},
        {"brGreen", &Colors::brGreen},     {"brYellow", &Colors::brYellow},
        {"brBlue", &Colors::brBlue},       {"brMagenta", &Colors::brMagenta},
        {"brCyan", &Colors::brCyan},       {"brWhite", &Colors::brWhite},
        {"bgBlack", &Colors::bgBlack},     {"bgRed", &Colors::bgRed},
        {"bgGreen", &Colors::bgGreen},     {"bgYellow", &Colors::bgYellow},
        {"bgBlue", &Colors::bgBlue},       {"bgMagenta", &Colors::bgMagenta},
        {"bgCyan", &Colors::bgCyan},       {"bgWhite", &Colors::bgWhite},
        {"bgBrBlack", &Colors::bgBrBlack}, {"bgBrRed", &Colors::bgBrRed},
        {"bgBrGreen", &Colors::bgBrGreen}, {"bgBrYellow", &Colors::bgBrYellow},
        {"bgBrBlue", &Colors::bgBrBlue},   {"bgBrMagenta", &Colors::bgBrMagenta},
        {"bgBrCyan", &Colors::bgBrCyan},   {"bgBrWhite", &Colors::bgBrWhite},
    };

    // Generate single color logs
    for (const auto &[name, color] : colorMap)
    {
        auto msg = LogMessage(LogSegment(name).colorize(*color));
        sink->pushLog(msg);
    }

    // Generate combinations of two colors
    for (size_t i = 0; i < std::size(colorMap); ++i)
    {
        for (size_t j = i + 1; j < std::size(colorMap); ++j)
        {
            std::string combinationName = std::string(colorMap[i].first) + "+" + colorMap[j].first;

            auto msg = LogMessage(LogSegment(combinationName).colorize(*colorMap[i].second, *colorMap[j].second));
            sink->pushLog(msg);
        }
    }
}

void threadLog(LogSink *sink)
{
    for (size_t i = 0; i < 10; i++)
    {
        auto msg = LogMessage("Log ")
                       .append(LogSegment("{} ", i).colorize(Colors::cyan))
                       .append(LogSegment("from thread 0x{:X}", GetCurrentThreadId()).colorize(Colors::green));
        sink->pushLog(msg);
        std::this_thread::yield(); // Let other threads execute.
    }

    sink->pushLog(LogMessage(LogSegment("Final log from thread: 0x{:X}", GetCurrentThreadId())));
}

std::unique_ptr<LogSink> switchToAsync()
{
    logger = std::make_shared<AsyncLogger>(); // Runtime change allowed!!
    logger->addBuffer(std::make_unique<ConsoleOutLogBuffer>("TEST"));
    std::static_pointer_cast<AsyncLogger>(logger)->spawnThread();

    return logger->createSink("TEST_ASYNC");
}

void testAsync(LogSink* sink)
{
    std::thread th1(threadLog, sink);
    std::thread th2(threadLog, sink);
    std::thread th3(threadLog, sink);
    std::thread th4(threadLog, sink);

    th1.join();
    th2.join();
    th3.join();
    th4.join();
}

/*
void testRuntimeError()
{
    EZLOGGER_LOG_RUNTIME_ERROR(
        logWorker, { throw std::runtime_error("Test C++ exception!"); });

    auto msg = std::make_unique<LogMessage>("");
    msg->setPrefix("RUNTIME", LogMessage::Color::GREEN);
    msg->green("std::runtime_error Logged successfully!");
    logWorker->log(std::move(msg));
    logWorker->flush();
}

void testSignalLogger()
{
    logWorker->attachSignalLogger();
    std::raise(SIGINT);
    logWorker->detachSignalLogger();

    auto msg = std::make_unique<LogMessage>("");
    msg->setPrefix("SIGNAL", LogMessage::Color::GREEN);
    msg->green("SIGINT Logged successfully!");
    logWorker->log(std::move(msg));
    logWorker->flush();
}
*/

/*
#ifdef EZLIB_WORKING_WINDOWS
void testVEHLogger()
{
    auto fix = [](EXCEPTION_POINTERS *exceptionInfo) -> LONG {
        if (exceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_INT_DIVIDE_BY_ZERO)
        {
            exceptionInfo->ContextRecord->Rip += 2;
            // Skip the instruction.
            return EXCEPTION_CONTINUE_EXECUTION;
        }

        return EXCEPTION_CONTINUE_SEARCH; // Should make the program crash...
    };
    auto vehHandle = AddVectoredExceptionHandler(0, fix); // Add a handler to fix the exp.
    logWorker->attachVehLogger();

    asm("push %rbx;");
    asm("push %rdx;");
    asm("push %rax;");

    asm("xor %ebx, %ebx;"); // Se divisor to 0, we don't care about dividend.
    asm("idiv %ebx;"); // Ensure compiler produces the instruction we want (size 2).

    asm("pop %rax;");
    asm("pop %rdx;");
    asm("pop %rbx;");

    logWorker->detachVehLogger();
    RemoveVectoredExceptionHandler(vehHandle); // Remove the handler used to fix the exp.

    auto msg = std::make_unique<LogMessage>("");
    msg->setPrefix("VEH", LogMessage::Color::GREEN);
    msg->green("EXCEPTION_INT_DIVIDE_BY_ZERO Logged successfully!");
    logWorker->log(std::move(msg));
    logWorker->flush();
}

void testUEFLogger()
{
    logWorker->attachUefLogger();
    logWorker->detachUefLogger();
    auto msg = std::make_unique<LogMessage>("");
    msg->setPrefix("UEF", LogMessage::Color::GREEN);
    msg->green("UEF handler attached and detached successfully!");
    logWorker->log(std::move(msg));
    logWorker->flush();
}
#endif
 */

/**
 * @TEST These tests must be checked manually.
 */
int main()
{
    logger = std::make_shared<SyncLogger>();
    logger->addBuffer(std::make_unique<ConsoleOutLogBuffer>("TEST"));

    std::unique_ptr<LogSink> testSink = logger->createSink(LogSegment("TEST_SYNC").colorize(Colors::red));

    testSync(testSink.get());
    testSink = switchToAsync();
    testAsync(testSink.get());
    /*
    testRuntimeError();
    testSignalLogger();

#ifdef EZLIB_WORKING_WINDOWS
    testVEHLogger();
    testUEFLogger();
#endif*/

    return 0;
}

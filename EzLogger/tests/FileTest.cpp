#include "EzLogger.h"

std::shared_ptr<FileLogWorker> logWorker;

void testSync(LogSink *sink)
{
    LogMessage("This word should be default").log(sink);

    LogMessage("This word should be ").black("black").log(sink);
    LogMessage("This word should be ").red("red").log(sink);
    LogMessage("This word should be ").green("green").log(sink);
    LogMessage("This word should be ").yellow("yellow").log(sink);
    LogMessage("This word should be ").blue("blue").log(sink);
    LogMessage("This word should be ").magenta("magenta").log(sink);
    LogMessage("This word should be ").cyan("cyan").log(sink);
    LogMessage("This word should be ").white("white").log(sink);

    LogMessage("This word should be ").brightBlack("brightBlack").log(sink);
    LogMessage("This word should be ").brightRed("brightRed").log(sink);
    LogMessage("This word should be ").brightGreen("brightGreen").log(sink);
    LogMessage("This word should be ").brightYellow("brightYellow").log(sink);
    LogMessage("This word should be ").brightBlue("brightBlue").log(sink);
    LogMessage("This word should be ").brightMagenta("brightMagenta").log(sink);
    LogMessage("This word should be ").brightCyan("brightCyan").log(sink);
    LogMessage("This word should be ").brightWhite("brightWhite").log(sink);

    LogMessage("This word should be ").bgBlack("bgBlack").log(sink);
    LogMessage("This word should be ").bgRed("bgRed").log(sink);
    LogMessage("This word should be ").bgGreen("bgGreen").log(sink);
    LogMessage("This word should be ").bgYellow("bgYellow").log(sink);
    LogMessage("This word should be ").bgBlue("bgBlue").log(sink);
    LogMessage("This word should be ").bgMagenta("bgMagenta").log(sink);
    LogMessage("This word should be ").bgCyan("bgCyan").log(sink);
    LogMessage("This word should be ").bgWhite("bgWhite").log(sink);

    LogMessage("This word should be ").bgBrightBlack("bgBrightBlack").log(sink);
    LogMessage("This word should be ").bgBrightRed("bgBrightRed").log(sink);
    LogMessage("This word should be ").bgBrightGreen("bgBrightGreen").log(sink);
    LogMessage("This word should be ").bgBrightYellow("bgBrightYellow").log(sink);
    LogMessage("This word should be ").bgBrightBlue("bgBrightBlue").log(sink);
    LogMessage("This word should be ").bgBrightMagenta("bgBrightMagenta").log(sink);
    LogMessage("This word should be ").bgBrightCyan("bgBrightCyan").log(sink);
    LogMessage("This word should be ").bgBrightWhite("bgBrightWhite").log(sink);

    LogMessage("This word should be ").bold("bold").log(sink);
    LogMessage("This word should be ").dim("dim").log(sink);
    LogMessage("This word should be ").italic("italic").log(sink);
    LogMessage("This word should be ").underline("underline").log(sink);
    LogMessage("This word should be ").blink("blink").log(sink);
    LogMessage("This word should be ").reverse("reverse").log(sink);
    LogMessage("This word should be ").hidden("hidden").log(sink);
    LogMessage("This word should be ").strike("strike").log(sink);

    LogMessage("This paragraph contains all the available options ")
        .black("black ")
        .red("red ")
        .green("green ")
        .yellow("yellow ")
        .blue("blue ")
        .magenta("magenta ")
        .cyan("cyan ")
        .white("white ")
        .brightBlack("brightBlack ")
        .brightRed("brightRed ")
        .brightGreen("brightGreen\n")
        .brightYellow("brightYellow ")
        .brightBlue("brightBlue ")
        .brightMagenta("brightMagenta ")
        .brightCyan("brightCyan ")
        .brightWhite("brightWhite ")
        .bgBlack("bgBlack ")
        .bgRed("bgRed ")
        .bgGreen("bgGreen ")
        .bgYellow("bgYellow ")
        .bgBlue("bgBlue ")
        .bgMagenta("bgMagenta")
        .bgCyan("bgCyan ")
        .bgWhite("bgWhite ")
        .bgBrightBlack("bgBrightBlack\n")
        .bgBrightRed("bgBrightRed ")
        .bgBrightGreen("bgBrightGreen ")
        .bgBrightYellow("bgBrightYellow ")
        .bgBrightBlue("bgBrightBlue ")
        .bgBrightMagenta("bgBrightMagenta ")
        .bgBrightCyan("bgBrightCyan ")
        .bgBrightWhite("bgBrightWhite ")
        .log(sink);

    LogMessage("This is a ").cyan("{}", "formatted ").green("coloured ").red("text ").bold("{}", "!").log(sink);
}

void threadLog(LogSink *sink)
{
    for (size_t i = 0; i < 10; i++)
    {
        LogMessage("Log ").cyan("{} ", i).green("from ").red("thread ").bold("0x{:X}", GetCurrentThreadId()).log(sink);
        std::this_thread::yield(); // Let other threads execute.
    }

    LogMessage("Final pushLog from thread: 0x{:X}", GetCurrentThreadId()).log(sink);
}

void testAsync(LogSink *sink)
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

void testRuntimeError()
{
    EZLOGGER_LOG_RUNTIME_ERROR(logWorker, { throw std::runtime_error("Test C++ exception!"); });

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
    asm("idiv %ebx;");      // Ensure compiler produces the instruction we want (size 2).

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

/**
 * @TEST These tests must be checked manually. On the file.
 * If console tests worked this should work too. The most important thing
 * to check is that pushLog messages DO NOT contains color escape characters.
 */
int main()
{
    logWorker = std::make_shared<FileLogWorker>(std::filesystem::current_path() / "pushLog.txt",
                                                FileLogWorker::AppendTimestamp | FileLogWorker::EnsureUnique);
    std::unique_ptr<LogSink> testSink = std::make_unique<LogSink>("TEST_SINK", LogMessage::Color::CYAN, logWorker);

    testSync(testSink.get());
    testAsync(testSink.get());
    testRuntimeError();
    testSignalLogger();
#ifdef EZLIB_WORKING_WINDOWS
    testVEHLogger();
    testUEFLogger();
#endif

    return 0;
}
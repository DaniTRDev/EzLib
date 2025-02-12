#include "EzLogger.h"

std::shared_ptr<Logger> logger;

void testSync(LogSink *sink)
{
	sink->pushLog(LogMessage("").add("This word should be default"));

	static const std::pair<const char *, const SimpleColor *> colorMap[] = {
			{ "bold",        &Colors::bold },
			{ "dim",         &Colors::dim },
			{ "italic",      &Colors::italic },
			{ "underline",   &Colors::underline },
			{ "blink",       &Colors::blink },
			{ "reverse",     &Colors::reverse },
			{ "hidden",      &Colors::hidden },
			{ "strike",      &Colors::strike },
			{ "black",       &Colors::black },
			{ "red",         &Colors::red },
			{ "green",       &Colors::green },
			{ "yellow",      &Colors::yellow },
			{ "blue",        &Colors::blue },
			{ "magenta",     &Colors::magenta },
			{ "cyan",        &Colors::cyan },
			{ "white",       &Colors::white },
			{ "brBlack",     &Colors::brBlack },
			{ "brRed",       &Colors::brRed },
			{ "brGreen",     &Colors::brGreen },
			{ "brYellow",    &Colors::brYellow },
			{ "brBlue",      &Colors::brBlue },
			{ "brMagenta",   &Colors::brMagenta },
			{ "brCyan",      &Colors::brCyan },
			{ "brWhite",     &Colors::brWhite },
			{ "bgBlack",     &Colors::bgBlack },
			{ "bgRed",       &Colors::bgRed },
			{ "bgGreen",     &Colors::bgGreen },
			{ "bgYellow",    &Colors::bgYellow },
			{ "bgBlue",      &Colors::bgBlue },
			{ "bgMagenta",   &Colors::bgMagenta },
			{ "bgCyan",      &Colors::bgCyan },
			{ "bgWhite",     &Colors::bgWhite },
			{ "bgBrBlack",   &Colors::bgBrBlack },
			{ "bgBrRed",     &Colors::bgBrRed },
			{ "bgBrGreen",   &Colors::bgBrGreen },
			{ "bgBrYellow",  &Colors::bgBrYellow },
			{ "bgBrBlue",    &Colors::bgBrBlue },
			{ "bgBrMagenta", &Colors::bgBrMagenta },
			{ "bgBrCyan",    &Colors::bgBrCyan },
			{ "bgBrWhite",   &Colors::bgBrWhite },
	};

	// Generate single color logs
	for (const auto &[ name, color ]: colorMap)
	{
		auto msg = LogMessage("").add(name).colorize(*color);
		sink->pushLog(msg);
	}

	// Generate combinations of two colors
	for (size_t i = 0; i < std::size(colorMap); ++i)
	{
		for (size_t j = i + 1; j < std::size(colorMap); ++j)
		{
			std::string combinationName = std::string(colorMap[ i ].first) + "+" + colorMap[ j ].first;

			auto msg = LogMessage("").add(combinationName).colorize(*colorMap[ i ].second, *colorMap[ j ].second);
			sink->pushLog(msg);
		}
	}
}

void threadLog(LogSink *sink)
{
	for (size_t i = 0; i < 10; i++)
	{
		auto msg = LogMessage("Log ")
				.add("{} ", i).colorize(Colors::cyan)
				.add("from thread ")
				.add("0x{:X}", OsDependant::GetThreadId()).colorize(Colors::green);

		sink->pushLog(msg);
		std::this_thread::yield(); // Let other threads execute.
	}

	sink->pushLog(LogMessage("").add("Final log from thread: 0x{:X}", OsDependant::GetThreadId()));
}

void switchToAsync()
{
	auto sync = std::static_pointer_cast<SyncLogger>(logger);

	logger = std::move(sync->switchToAsync());
	auto async = std::static_pointer_cast<AsyncLogger>(logger);

	std::cout << "Spawning thread to log" << std::endl;
	async->spawnThread();

	int timeout = 0;
	while (!async->isInternalThreadAlive())
	{
		if (timeout == 3)
		{
			std::cout << "Ran out of time for the creation of the log thread!!" << std::endl;
			return;
		}

		timeout++;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
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

void testRuntimeError(LogSink *errorSink, LogSink *debugSink)
{
	EZLOGGER_LOG_TRY_CATCH(errorSink, { throw std::runtime_error("Test C++ exception!"); });

	LogMessage msg = LogMessage("").add("std::runtime_error Logged successfully!");
	debugSink->pushLog(msg);
}

void testSignalLogger(ExceptionSink *exceptionLogger, LogSink *debugSink)
{
	exceptionLogger->attachSignalLogger();
	std::raise(SIGINT);
	exceptionLogger->detachSignalLogger();

	LogMessage msg = LogMessage("").add("Signal Logged successfully!");
	debugSink->pushLog(msg);
}

#ifdef EZLIB_WORKING_WINDOWS
void testVEHLogger(WindowsExceptionSink *exceptionLogger, LogSink *debugSink)
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
	exceptionLogger->attachWindowsLogger();

	asm("push %rbx;");
	asm("push %rdx;");
	asm("push %rax;");

	asm("xor %ebx, %ebx;"); // Se divisor to 0, we don't care about dividend.
	asm("idiv %ebx;");      // Ensure compiler produces the instruction we want (size 2).

	asm("pop %rax;");
	asm("pop %rdx;");
	asm("pop %rbx;");

	exceptionLogger->detachWindowsLogger();
	RemoveVectoredExceptionHandler(vehHandle); // Remove the handler used to fix the exp.

	LogMessage msg = LogMessage("").add("Windows exception logged successfully!");
	debugSink->pushLog(msg);
}
#endif

/**
 * @TEST These tests must be checked manually.
 */
int main()
{
	try
	{
		logger = EzLogger::createSinkLogger("TEST");
		std::shared_ptr<LogSink> testSink = logger->createSink<LogSink>(LogSegment("TEST_SYNC").colorize(Colors::red));

#ifdef EZLIB_WORKING_WINDOWS
		std::shared_ptr<WindowsExceptionSink> exceptionSink =
			logger->createSink<WindowsExceptionSink>(LogSegment("EXCEPTION_SYNC").colorize(Colors::bold, Colors::red));
#elif defined(EZLIB_WORKING_UNIX)
		std::shared_ptr<ExceptionSink> exceptionSink =
				logger->createSink<ExceptionSink>(LogSegment("EXCEPTION_SYNC").colorize(Colors::bold, Colors::red));
#endif

		testSync(testSink.get());
		switchToAsync();
		testAsync(testSink.get());
		testRuntimeError(exceptionSink.get(), testSink.get());
		testSignalLogger(exceptionSink.get(), testSink.get());

#ifdef EZLIB_WORKING_WINDOWS
		testVEHLogger(exceptionSink.get(), testSink.get());
#endif
	}
	catch (std::runtime_error err)
	{
		std::cout << "ERROR RECEIVED DURING TESTS: " << err.what() << std::endl;
		return -1;
	}

	return 0;
}

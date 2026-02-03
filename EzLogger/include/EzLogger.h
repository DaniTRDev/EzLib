#ifndef EZLOGGER_EZLOGGER_H
#define EZLOGGER_EZLOGGER_H

#include "LogMessage/LogMessage.h"

#include "ILogger.h"
#include "ILogSink.h"

#include "LogSinks/ExceptionSink.h"
#include "LogSinks/WindowsExceptionSink.h"

#include "Loggers/AsyncLogger.h"
#include "Loggers/SyncLogger.h"

#include "OutLogBuffers/ConsoleOutLogBuffer.h"
#include "OutLogBuffers/FileOutLogBuffer.h"

namespace EzLogger
{
	extern std::unique_ptr<SyncLogger> createSyncLogger(std::string_view consoleTittle, std::filesystem::path filePath = "");
};

#endif // EZLOGGER_EZLOGGER_H

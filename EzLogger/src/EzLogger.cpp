#include "EzLogger.h"

namespace EzLogger
{
	std::unique_ptr<SyncLogger> createSyncLogger(std::string_view consoleTittle, std::filesystem::path filePath)
	{
        std::unique_ptr<ConsoleOutLogBuffer> consoleBuff = std::make_unique<ConsoleOutLogBuffer>(consoleTittle);
        std::unique_ptr<FileOutLogBuffer> fileBuff = std::make_unique<FileOutLogBuffer>(filePath);
        std::unique_ptr<SyncLogger> sync = std::make_unique<SyncLogger>();
        
        if (!consoleBuff->open())
        {
            throw std::runtime_error("Could not open console buffer");
        }
        
		sync->addBuffer(std::move(consoleBuff));
        
        if (filePath != "")
        {
            if (fileBuff->open())
            {
                sync->pushLog(LogMessage("Opened log file at {}", filePath.string()));
                sync->addBuffer(std::move(fileBuff));
            }
            else
            {
                sync->pushLog(LogMessage("Could not open out log file at {}", filePath.string()));
            }
            
        }
        
		return std::move(sync);
	}
}
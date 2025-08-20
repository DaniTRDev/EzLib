#include "EzLogger.h"

namespace EzLogger
{
	std::unique_ptr<SyncLogger> createSinkLogger(std::string_view consoleTittle, std::filesystem::path filePath)
	{
		std::unique_ptr<SyncLogger> sync = std::make_unique<SyncLogger>();
		sync->addBuffer(std::make_unique<ConsoleOutLogBuffer>(consoleTittle));
        
        if (filePath != "")
        {
            std::unique_ptr<FileOutLogBuffer> fileBuff = std::make_unique<FileOutLogBuffer>(filePath);
            
            if (!fileBuff->open())
                sync->pushLog(LogMessage("Could not open out log file!"));
            else
                sync->pushLog(LogMessage("Opened log file at {}", filePath.string()));
            
            sync->addBuffer(std::move(fileBuff));
        }
        
		return std::move(sync);
	}
}
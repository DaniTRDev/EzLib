#include "EzLogger.h"

namespace EzLogger
{
	std::unique_ptr<SyncLogger> createSinkLogger(std::string_view consoleTittle)
	{
		std::unique_ptr<SyncLogger> sync = std::make_unique<SyncLogger>();
		sync->addBuffer(std::make_unique<ConsoleOutLogBuffer>(consoleTittle));

		return std::move(sync);
	}
}
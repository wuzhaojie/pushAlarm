#ifndef _LOG_H_
#define _LOG_H_
#include "Poco/Logger.h"

using  Poco::Logger;

namespace Mylog
{
	#define logger_handle  (Logger::get("logger"))
	void Logger_initiation();
	void Setup_logger();
}

#endif//_LOG_H_
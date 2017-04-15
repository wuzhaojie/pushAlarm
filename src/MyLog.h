#ifndef _MY_LOG_H_
#define _MY_LOG_H_
#include "Poco/Logger.h"

using  Poco::Logger;

class logg
{
public:
	static void sington();
	~logg();

public:
	static Poco::Logger& _log;
};

#endif//_MY_LOG_H_
#include "Poco/AutoPtr.h"
#include "poco/Util/PropertyFileConfiguration.h"
#include "poco/Util/LoggingConfigurator.h"
#include "Log.h"

using namespace Poco;
//消息等级//目前程序中使用到的有:PRIO_ERROR，PRIO_WARNING，PRIO_INFORMATION
/*
PRIO_FATAL = 1,   
PRIO_CRITICAL,    
PRIO_ERROR,       
PRIO_WARNING,     
PRIO_NOTICE,      
PRIO_INFORMATION, 
PRIO_DEBUG,       
PRIO_TRACE        
*/
namespace Mylog
{   
	void Logger_initiation()
	{
		Poco::AutoPtr<Poco::Util::PropertyFileConfiguration> pConf =  new Poco::Util::PropertyFileConfiguration("./log_conf.properties");
		Poco::Util::LoggingConfigurator log_configurator; 
		log_configurator.configure(pConf);
		Poco::Logger::root();
		return;
	}

	void Setup_logger()
	{
		static bool b_setup =false; 
		if (! b_setup)
		{
			b_setup =true;  
			Logger_initiation();
		}
		return;
	}
}
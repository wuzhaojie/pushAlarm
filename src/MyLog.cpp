#include "Poco/AutoPtr.h"
#include "poco/Util/PropertyFileConfiguration.h"
#include "poco/Util/LoggingConfigurator.h"
#include "MyLog.h"

using Poco::Logger;

void logg::sington()
{
	static bool b_sington =false; 
	if (! b_sington)
	{
		b_sington =true;  
		Poco::AutoPtr<Poco::Util::PropertyFileConfiguration> pConf =  new Poco::Util::PropertyFileConfiguration("../bin/release/log_conf.properties");
		Poco::Util::LoggingConfigurator log_configurator; 
		log_configurator.configure(pConf);
		//logg::_log = Poco::Logger::root();
	}
}

logg::~logg()
{

}

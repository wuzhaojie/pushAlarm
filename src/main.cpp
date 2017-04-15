#include <Poco/Thread.h>
#include "TaskMmanager.h"
#include "Log.h"

using namespace Mylog;

int main(int argc, char** argv)
{
	Setup_logger();
	Poco::Mutex  mtx; 
	Poco::Thread thd_read,thd_push;
	ReadAlarm read(mtx);
	PushAlarm push(mtx);
	thd_read.start( read );
	//push线程要用到ReadConfig::strUrl,需要read线程先调用ReadConfig::ReadFile给ReadConfig::strUrl赋值。
	//Sleep(1)确保read线程读完配置文件。
	Sleep(1);
	thd_push.start( push );
	thd_read.join();
	thd_push.join();
	return 0;
}

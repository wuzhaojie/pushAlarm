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
	//push�߳�Ҫ�õ�ReadConfig::strUrl,��Ҫread�߳��ȵ���ReadConfig::ReadFile��ReadConfig::strUrl��ֵ��
	//Sleep(1)ȷ��read�̶߳��������ļ���
	Sleep(1);
	thd_push.start( push );
	thd_read.join();
	thd_push.join();
	return 0;
}

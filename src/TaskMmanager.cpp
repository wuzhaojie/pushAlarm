#include <list>
#include <WinSock2.h>
#include <Windows.h>
#include <Poco\ScopedLock.h>
#include "HttpClient.h"
#include "ReadConfig.h"
#include "pSpaceTreate.h"
#include "JsonTool.h"
#include "Log.h"
#include "TaskMmanager.h"

using namespace Mylog;

typedef std::list<std::string> StringList;
static StringList dataBuf;

ReadAlarm::~ReadAlarm()
{

}

void ReadAlarm::run()
{
	ReadConfig PSconfig;
	char filePath[] = "./config.ini";
	PSconfig.ReadFile(filePath);

	pSpacePara *PS  = PSconfig.GetPspaceParameter();
	std::string Port = (*PS).pspacePort;
	std::string IP = (*PS).pspaceIP;
	std::string Username = (*PS).pspaceUsername;
	std::string Password = (*PS).pspacePassword;
	int dump_sec = (*PS).dump_sec;
	
	PspaceTreate PStreat;
	PStreat.SetParameter(PS);
	bool isConnt  = PStreat.ConnectPs(PS);
	while(!isConnt)
	{
		Sleep(1000);
		isConnt  = PStreat.ConnectPs(PS);
	}
	delete PS;

	while(1)
	{		
		Sleep(1000);
		PStreat.QueryAlarmData();
		PS_ALARM * alarms = PStreat.GetAlarms();
		PSUINT32 alarmCount = PStreat.GetAlarmCount();
		JsonTool tool;
		std::string strTmp = tool.PS_ALARM_TO_JSON(alarms,alarmCount);
		if (strTmp.size())
		{
			bool bUnique = true;
			for (auto iter = dataBuf.begin();iter != dataBuf.end(); iter++)
			{
				if (*iter==strTmp)
				{
					bUnique = false;
				}
			}
			if (bUnique||(dataBuf.size()==0))
			{
				Poco::Mutex::ScopedLock lock(_mtx_read);
				dataBuf.push_back(strTmp);
				int count = dataBuf.size();
				std::string str = "databuf複%d訳方象";
				poco_warning_f1(logger_handle,JsonTool::strtoUTF8(str.c_str()),count);
			}
		}
		delete alarms;
	}
	return ;
}

PushAlarm::~PushAlarm()
{

}

void PushAlarm::run()
{
	HttpClient client;
	bool btmp = false;
	while (1)
	{
		Sleep(1000);
		if (dataBuf.size()>0)
		{
			Poco::Mutex::ScopedLock lock(_mtx_push);
			btmp = client.PushAlarmData_JSON((*dataBuf.begin()));
			if (btmp)
			{
				dataBuf.erase(dataBuf.begin());
				int count = dataBuf.size();
				std::string str = "databuf複%d訳方象";
				poco_warning_f1(logger_handle,JsonTool::strtoUTF8(str.c_str()),count);
			}else{
				std::string str = "容僕払移%s";
				poco_error_f1(logger_handle,JsonTool::strtoUTF8(str.c_str()),*dataBuf.begin());
				continue;
			}
		}
	}
	return ;
}

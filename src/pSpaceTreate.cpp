#include <string.h>
#include <time.h>
#include "Log.h"
#include "JsonTool.h"
#include "pSpaceTreate.h"

using namespace std;
using namespace Mylog;

PspaceTreate::PspaceTreate()
{
	hServer     = PSHANDLE_UNUSED;
	nRet        = PSRET_OK;
	pszServer   = PSNULL;
	pszUserName = PSNULL;
	pszPassword = PSNULL;
	m_pAlarms = PSNULL;
	m_nAlarmCount = 0;
}

PspaceTreate::~PspaceTreate()
{

}

bool PspaceTreate::ConnectPs( pSpacePara* connPS )
{
	//在使用pSpace API接口的时候必须首先调用psAPI_Common_StartAPI
	PSAPIStatus nRet = psAPI_Common_StartAPI();
	if ( PSERR(nRet) )
	{
		std::string str = "启动psAPI失败";
		poco_error(logger_handle,JsonTool::strtoUTF8(str.c_str()));
	}

	nRet = psAPI_Server_Connect((PSSTR)(*connPS).pspaceIP.c_str(),(PSSTR)(*connPS).pspaceUsername.c_str(),(PSSTR)(*connPS).pspacePassword.c_str(),&hServer);
	if (nRet == PSERR_NET_CONNECT_FAILED)
	{
		std::string str = "链接%s失败(pSpace未开启)";
		poco_error_f1(logger_handle,JsonTool::strtoUTF8(str.c_str()),JsonTool::strtoUTF8(pszServer));
		return false;
	}
	else if (nRet == PSERR_USER_USER_NOT_EXIST)
	{
		std::string str = "用户名%s不存在";
		poco_error_f1(logger_handle,JsonTool::strtoUTF8(str.c_str()),JsonTool::strtoUTF8(pszUserName));
		return false;
	}
	else if (nRet == PSERR_USER_USERNAME_OR_PASSWORD_NOTMATCH)
	{
		std::string str = "密码%s错误";
		poco_error_f1(logger_handle,JsonTool::strtoUTF8(str.c_str()),JsonTool::strtoUTF8(pszPassword));
		return false;
	}
	else if (PSERR(nRet))
	{
		std::string str = "链接失败%s";
		poco_error_f1(logger_handle,JsonTool::strtoUTF8(str.c_str()),JsonTool::strtoUTF8(psAPI_Commom_GetErrorDesc(nRet)));
		return false;
	}
	else
	{
		std::string str = "链接%s成功";
		poco_information_f1(logger_handle,JsonTool::strtoUTF8(str.c_str()),JsonTool::strtoUTF8(pszServer));
		return true;
	}
}

void PspaceTreate::DisconnectPs()
{
	nRet = psAPI_Server_Disconnect(hServer);
	if (PSERR(nRet))
	{
		std::string str = "断开连接失败错误 %s";
		poco_error_f1(logger_handle,JsonTool::strtoUTF8(str.c_str()),JsonTool::strtoUTF8(psAPI_Commom_GetErrorDesc(nRet)));
	}
	else
	{
		std::string str = "断开连接失败错误 %s";
		poco_error(logger_handle,JsonTool::strtoUTF8(str.c_str()));
	}
	psAPI_Common_StopAPI();
	return;
}

void  PspaceTreate::QueryAlarmData()
{
	PSAPIStatus nRet = PSRET_OK;
	PS_ALARM_FILTER_FIELD filterField = {0};
	PS_ALARM_FILTER filter = {0};
	PSUINT32 nAlarmCount = 0;
	PS_ALARM* pAlarms = PSNULL;
	PSUINT32 n = 0;
	filterField.TagId = PSTRUE;
	filter.TagId = 0;
	/*filterField.AlarmHighLevel = PSTRUE;
	filter.AlarmHighLevel = 2;
	filterField.AlarmLowLevel = PSTRUE;
	filter.AlarmLowLevel = 0;
	filterField.AlarmHaveAcked = PSTRUE;
	filter.AlarmHaveAcked = 0;*/
	/*
	PS_ALARM_TOPIC_QUALITY_CHANGE=0x01,	 质量戳改变
	PS_ALARM_TOPIC_VALUE_CHANGE = 0x02,	 值改变
	PS_ALARM_TOPIC_HIGH = 0x04,			 越高限
	PS_ALARM_TOPIC_HIGHHIGH = 0x08,		 越高高限
	PS_ALARM_TOPIC_LOW = 0x10,			 越低限
	PS_ALARM_TOPIC_LOWLOW = 0x20,		 越低低限
	PS_ALARM_TOPIC_CHANGERATE = 0x40,	 变化率报警
	PS_ALARM_TOPIC_WARP = 0x80,			 偏差报警
	*/

	nRet = psAPI_Alarm_Real_Query(hServer,&filterField, &filter, &nAlarmCount, &pAlarms);
	if (PSERR(nRet))
	{
		std::string str = "查询测点实时报警失败%s";
		poco_error_f1(logger_handle,JsonTool::strtoUTF8(str.c_str()),JsonTool::strtoUTF8(psAPI_Commom_GetErrorDesc(nRet)));
		return;
	}
	SetAlarmParam(pAlarms,nAlarmCount);
	{
		std::string str = "查询测点实时报警成功,返回数量%u";
		poco_information_f1(logger_handle,JsonTool::strtoUTF8(str.c_str()),nAlarmCount);
	}
	psAPI_Memory_FreeAlarmList(&pAlarms, nAlarmCount);
	return;
}

void PspaceTreate::SetParameter(const pSpacePara* ps)
{
	pszServer = (PSSTR)(*ps).pspaceIP.c_str();
	pszUserName = (PSSTR)(*ps).pspaceUsername.c_str();
	pszPassword = (PSSTR)(*ps).pspacePassword.c_str();
	return;
}

pSpacePara* PspaceTreate::GetParameter()
{
	pSpacePara* ps;
	(*ps).pspaceIP = pszServer;
	(*ps).pspacePassword = pszPassword;
	(*ps).pspaceUsername = pszUserName;
	return ps;
}

PS_ALARM* PspaceTreate::GetAlarms()
{
	PS_ALARM* tmp = PSNULL;
	if (m_pAlarms!=PSNULL)
	{
		if (m_nAlarmCount)
		{
			tmp = new PS_ALARM[m_nAlarmCount];
		}
		for(int n = 0; n < m_nAlarmCount; n++)
		{	
			tmp[n].AlarmId = m_pAlarms[n].AlarmId;
			tmp[n].TagId = m_pAlarms[n].TagId;
			tmp[n].UserID = m_pAlarms[n].UserID;
			tmp[n].AppType = m_pAlarms[n].AppType;
			tmp[n].AlarmLevel = m_pAlarms[n].AlarmLevel;
			tmp[n].AlarmContent = new char[256];
			std::strcpy(tmp[n].AlarmContent,m_pAlarms[n].AlarmContent);
			tmp[n].AlarmValue = new char[256];
			std::strcpy(tmp[n].AlarmValue,m_pAlarms[n].AlarmValue);
			tmp[n].AlarmAckUserName = new char[256];
			std::strcpy(tmp[n].AlarmAckUserName,m_pAlarms[n].AlarmAckUserName);
			tmp[n].AlarmTopic = m_pAlarms[n].AlarmTopic;
			tmp[n].AlarmNeedAck = m_pAlarms[n].AlarmNeedAck;
			tmp[n].AlarmHaveAcked = m_pAlarms[n].AlarmHaveAcked;
			tmp[n].AlarmStartTime = m_pAlarms[n].AlarmStartTime;		
			tmp[n].AlarmEndTime = m_pAlarms[n].AlarmEndTime;
			tmp[n].AlarmAckedId = m_pAlarms[n].AlarmAckedId;
			tmp[n].AlarmAckTime = m_pAlarms[n].AlarmAckTime;
		}
	}
	return tmp;
}

PSUINT32 PspaceTreate::GetAlarmCount()
{
	return m_nAlarmCount;
}

void PspaceTreate::SetAlarmParam( PS_ALARM *pAlarms,PSUINT32 nAlarmCount )
{
	m_nAlarmCount = nAlarmCount;
	m_pAlarms = new PS_ALARM[nAlarmCount];
	for(int n = 0; n < nAlarmCount; n++)
	{	
		m_pAlarms[n].AlarmId = pAlarms[n].AlarmId;
		m_pAlarms[n].TagId = pAlarms[n].TagId;
		m_pAlarms[n].UserID = pAlarms[n].UserID;
		m_pAlarms[n].AppType = pAlarms[n].AppType;
		m_pAlarms[n].AlarmLevel = pAlarms[n].AlarmLevel;
		m_pAlarms[n].AlarmContent = new char[256];
		std::strcpy(m_pAlarms[n].AlarmContent,pAlarms[n].AlarmContent);
		m_pAlarms[n].AlarmValue = new char[256];
		std::strcpy(m_pAlarms[n].AlarmValue,pAlarms[n].AlarmValue);
		m_pAlarms[n].AlarmAckUserName = new char[256];
		std::strcpy(m_pAlarms[n].AlarmAckUserName,pAlarms[n].AlarmAckUserName);
		m_pAlarms[n].AlarmTopic = pAlarms[n].AlarmTopic;
		m_pAlarms[n].AlarmNeedAck = pAlarms[n].AlarmNeedAck;
		m_pAlarms[n].AlarmHaveAcked = pAlarms[n].AlarmHaveAcked;
		m_pAlarms[n].AlarmStartTime = pAlarms[n].AlarmStartTime;		
		m_pAlarms[n].AlarmEndTime = pAlarms[n].AlarmEndTime;
		m_pAlarms[n].AlarmAckedId = pAlarms[n].AlarmAckedId;
		m_pAlarms[n].AlarmAckTime = pAlarms[n].AlarmAckTime;
	}
	return ;
}

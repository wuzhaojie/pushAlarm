#ifndef _PSAPCE_TREATE_H_
#define _PSAPCE_TREATE_H_
#include "ReadConfig.h"

class PspaceTreate
{
public:
	PspaceTreate();
	~PspaceTreate();

public:
	bool ConnectPs(pSpacePara* connPS);
	void DisconnectPs();
	void ReConnect(int is_continue);
	void QueryAlarmData();
	void SetAlarmParam(PS_ALARM* pAlarms,PSUINT32 nAlarmCount);
	PS_ALARM* GetAlarms();
	PSUINT32 GetAlarmCount();
	void SetParameter(const pSpacePara* ps);
	pSpacePara* GetParameter();
public:
	PSHANDLE hServer;
	PSAPIStatus nRet;
	PSSTR pszServer;
	PSSTR pszUserName;
	PSSTR pszPassword;

	//用来存储查询到的报警数据
	PS_ALARM* m_pAlarms;
	PSUINT32 m_nAlarmCount;
};

#endif//_PSAPCE_TREATE_H_
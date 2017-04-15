#ifndef _JSON_TOOL_H_
#define _JSON_TOOL_H_
#include "psAPISDK.h"

class JsonTool{
public:
	JsonTool();
	~JsonTool();
	//���� ��PSUINT32 nAlarmCount���͡�PS_ALARM *pAlarms��ƴJSON���顣
	std::string  PS_ALARM_TO_JSON(PS_ALARM* pAlarms,PSUINT32 AlarmCount);
	static char* PSTIME2STR(PS_TIME ptm);
	static std::string strtoUTF8(const char* str);
	static std::string UTF8toStr(std::string str8);
};
#endif//_JSON_TOOL_H_
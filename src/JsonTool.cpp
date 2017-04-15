#include "poco/UTF8String.h"
#include "poco/UnicodeConverter.h"
#include "json.h"
#include "Log.h"
#include "JsonTool.h"

using namespace Mylog;

JsonTool::JsonTool()
{

}

JsonTool::~JsonTool()
{

}

std::string JsonTool::PS_ALARM_TO_JSON( PS_ALARM* pAlarms,PSUINT32 AlarmCount )
{
	Json::Value arr;
	Json::Value object;
	Json::StyledWriter writer;
	std::string str;
	for(int n = 0; n < AlarmCount; n++)
	{
		object["AlarmId"] = pAlarms[n].AlarmId;
		object["TagId"] = pAlarms[n].TagId;
		object["UserID"] = pAlarms[n].UserID;
		object["AppType"] = pAlarms[n].AppType;
		object["AlarmLevel"] = pAlarms[n].AlarmLevel;
		object["AlarmContent"] = pAlarms[n].AlarmContent;
		object["AlarmValue"] = pAlarms[n].AlarmValue;
		object["AlarmTopic"] = pAlarms[n].AlarmTopic;
		object["AlarmNeedAck"] = pAlarms[n].AlarmNeedAck;
		object["AlarmHaveAcked"] = pAlarms[n].AlarmHaveAcked;
		object["AlarmStartTime"] = JsonTool::PSTIME2STR(pAlarms[n].AlarmStartTime);
		object["AlarmStartTime"] = JsonTool::PSTIME2STR(pAlarms[n].AlarmEndTime);
		object["AlarmAckedId"] = pAlarms[n].AlarmAckedId;
		object["AlarmStartTime"] = JsonTool::PSTIME2STR(pAlarms[n].AlarmAckTime);
		arr.append(object);
	}
	if (arr.size()!=0)
	{
		str = writer.write(arr);
		std::string str1 = "转换PS_ALARM为JSON:%s";
		poco_information_f1(logger_handle,JsonTool::strtoUTF8(str1.c_str()),str);
	}else{
		std::string str = "暂无报警数据";
		poco_warning(logger_handle,JsonTool::strtoUTF8(str.c_str()));
	}
	return str;
}

char* JsonTool::PSTIME2STR(PS_TIME psTm)
{
	static char pszTime[256] = {0};
	time_t tt = psTm.Second;
	struct tm* ptm =  localtime(&(tt));
	sprintf(pszTime,"%04d-%02d-%02d %02d:%02d:%02d.%03d",ptm->tm_year+1900,
		ptm->tm_mon+1,ptm->tm_mday,ptm->tm_hour,ptm->tm_min,ptm->tm_sec,psTm.Millisec);
	return pszTime;
}

//!	将C++字符转为UTF8编码，主要用于Poco中文路径
/*!
	\param[in] str	需要转换的C++字符串
	\return	UTF8编码的字符串
*/
std::string JsonTool::strtoUTF8(const char* str)
{
#if defined (POCO_WIN32_UTF8) 
	std::string s = str;
	setlocale(LC_ALL, "chs");   
	const char* _Source = s.c_str();  
	size_t _Dsize = s.size() + 1;  
	Poco::UTF16Char* _Dest = new wchar_t[_Dsize];  
	wmemset(_Dest, 0, _Dsize);  
	mbstowcs(_Dest, _Source, _Dsize);
	Poco::UTF16String result = _Dest;  
	delete []_Dest;  
	setlocale(LC_ALL, "C"); 

	std::string utf8str;
	Poco::UnicodeConverter::convert(result, utf8str); 

	return utf8str;
#else
	return str;
#endif
}

//!	将UTF8编码的字符串转为C++字符串，主要用于输出Poco中文路径
/*!
	\param[in]	str8 需要转换的UTF8编码的字符串
	\return	C++字符串
*/
std::string JsonTool::UTF8toStr(std::string str8)
{
#if defined (POCO_WIN32_UTF8)  
	setlocale(LC_ALL, "chs");
	Poco::UTF16String str16;
	Poco::UnicodeConverter::convert(str8, str16);
	Poco::UTF16Char* char16 = (Poco::UTF16Char*)str16.c_str();
	size_t _Dsize = (str16.size() + 1) * 2;
	char* char8 = (char*)malloc(_Dsize);
	memset(char8, 0, _Dsize);
	wcstombs(char8, char16, _Dsize);

	std::string str = char8;
	delete[]char8;

	setlocale(LC_ALL, "C"); 

	return str;

#else
	return str8;
#endif
}
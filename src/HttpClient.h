#ifndef _HTTP_CLIENT_H_
#define _HTTP_CLIENT_H_
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <POCO/Net/HttpClientSession.h>
#include <POCO/Net/HTTPRequest.h>
#include <POCO/Net/HTTPResponse.h>

class HttpClient
{
public:
	HttpClient();
	~HttpClient();
	//将报警数据拼接成的JSON字符串推送到指定的restful接口。
	//strAlarm是由JSON对象格式化来的。
	bool PushAlarmData_JSON( const std::string& strAlarm);
public:
	Poco::Net::HTTPRequest m_req;
	Poco::Net::HTTPClientSession m_session;
};
#endif//_HTTP_CLIENT_H_

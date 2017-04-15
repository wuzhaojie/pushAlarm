#include <streambuf> 
#include <WinSock2.h>
#include <Windows.h>
#include <stdexcept>
#include <exception>
#include <POCO/Net/HTTPCredentials.h>
#include <POCO/Net/HTTPBasicCredentials.h>
#include <POCO/URI.h>
#include <POCO/StreamCopier.h>
#include "JsonTool.h"
#include "Log.h"
#include "ReadConfig.h"
#include "HttpClient.h"

using namespace Mylog;
using namespace  Poco;

HttpClient::HttpClient()
{
	std::string strURI = ReadConfig::strUrl; 
	//std::string strURI = "http://127.0.0.1:3000/test"; 
	Poco::URI uri(strURI); 
	m_session.setHost(uri.getHost());
	m_session.setPort(uri.getPort());
	m_req.setMethod("POST");
	m_req.setURI(strURI);
}

HttpClient::~HttpClient()
{

}

bool HttpClient::PushAlarmData_JSON(const std::string& strAlarm)
{
	//添加(基础验证信息)用户名，密码
	Poco::Net::HTTPBasicCredentials cred("domain\\uid", "password");
	cred.authenticate(m_req);

	//添加要发送的消息格式//发送json格式
	m_req.setContentType("application/json");
	m_req.setContentLength(strAlarm.length());
	try
	{
		m_session.sendRequest(m_req) << strAlarm;
	}
	catch (...)
	{
		std::string str = "数据推送至restFul接口出现异常";
		poco_error(logger_handle,JsonTool::strtoUTF8(str.c_str()));
		std::string strURI = ReadConfig::strUrl; 
		Poco::URI uri(strURI); 
		m_session.setHost(uri.getHost());
		m_session.setPort(uri.getPort());
		m_req.setMethod("POST");
		m_req.setURI(strURI);
		return false;
	}

    //接收restful接口返回数据
    Poco::Net::HTTPResponse res;
	std::string responseText;
    Poco::StreamCopier copier;
	try
	{
		std::istream& rs = m_session.receiveResponse(res);
		copier.copyToString(rs, responseText);
		std::cout << responseText << std::endl;
	}
	catch (...)
	{
		std::string str = "接收restFul接口返回数据异常";
		poco_error(logger_handle,JsonTool::strtoUTF8(str.c_str()));
		return false;
	}
	return true ;
}





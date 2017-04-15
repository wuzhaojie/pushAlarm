#include "Log.h"
#include "JsonTool.h"
#include "ReadConfig.h"

using namespace Mylog;
std::string ReadConfig::strUrl = "";
ReadConfig::ReadConfig()
{
	psParameter = new pSpacePara();
	(*psParameter).pspaceIP.clear();
	(*psParameter).pspacePassword.clear();
	(*psParameter).pspacePort.clear();
	(*psParameter).pspaceUsername.clear();

	configFileName = new char[256];
	memset(configFileName,0,sizeof(configFileName));
}

ReadConfig::~ReadConfig()
{

}

void ReadConfig::ReadFile(char *parameterFile)
{ 
	if(parameterFile == NULL) return;
	FILE *fp = fopen(parameterFile,"r");
	if(fp == NULL)
	{
		std::string str  = "加载配置文件失败";
		poco_error(logger_handle,JsonTool::strtoUTF8(str.c_str()));
		return;
	}
	char temp[256] = {0};
	char left[256] = {0};
	char right[256] = {0};
	while(fgets(temp,127,fp))
	{
		if(temp[0] == '[' || temp[0] == ';' || temp[0] == ' ') continue;
		sscanf(temp,"%s %*s %s",left,right);       
		if(strcmp(left,"server_ip")==0)
		{
			(*psParameter).pspaceIP = right;
		}
		if(strcmp(left,"server_username")==0)
		{
			(*psParameter).pspaceUsername = right;
		}
		if(strcmp(left,"server_password")==0)
		{
			(*psParameter).pspacePassword = right;
		}
		if(strcmp(left,"server_port")==0)
		{
			if (atoi(right)>0)
			{
				(*psParameter).pspacePort = right;
			}else{
				std::string  str =  "端口号不合法,使用默认值8889";
				poco_error(logger_handle,JsonTool::strtoUTF8(str.c_str()));
				(*psParameter).pspacePort = "8889";
			}
		}
		if(strcmp(left,"dump_sec")==0)
		{
			if (atoi(right)>0)
			{
				(*psParameter).dump_sec = atoi(right);
			}else{
				std::string  str =  "读取周期不合法，使用默认值500";
				poco_error(logger_handle,JsonTool::strtoUTF8(str.c_str()));
				(*psParameter).dump_sec = 500;
			}
		}
		if(strcmp(left,"strUrl")==0)
		{
			ReadConfig::strUrl = right;
		}
		memset(temp,0,256);
		memset(left,0,256);
		memset(right,0,256);
	}
	fclose(fp);//关闭文件句柄
	fp = NULL;
	return;
}
pSpacePara *ReadConfig::GetPspaceParameter() const
{
	return psParameter;
}
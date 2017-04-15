#ifndef _READCONFIG_H_
#define _READCONFIG_H_
#include "psAPISDK.h"

struct pSpacePara
{
	 std::string pspacePort;
	 std::string pspaceIP;
	 std::string pspaceUsername;
	 std::string pspacePassword;
	 int dump_sec;
};

class ReadConfig
{
public:
	ReadConfig();
	~ReadConfig();

public:
    void ReadFile(char* parameterFile);
	pSpacePara* GetPspaceParameter() const;

private:
	//pspace
	pSpacePara* psParameter;
	//ini
	char* configFileName;

public:
	//httpClient
	static std::string strUrl;
};

#endif 
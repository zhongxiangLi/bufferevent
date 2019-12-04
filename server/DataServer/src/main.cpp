

#include <string>

#include "common.h"
#include "global.h"

#include "LogServer.h"
#include "EventMain.h"
#include "tinyxml2.h"


using namespace tinyxml2;
#ifdef WIN32
#include "winsock2.h"
#endif

int main(int argc,char*argv[])
{
	if(!g_LogSrv.init("../../config/log4z.cfg"))
	{   
		printf("g_logsrc init fail!!!!\n");
		return 0;
	}

	//load xml 

	XMLDocument xmlDoc;
	XMLError eResult = xmlDoc.LoadFile("../../config/public_config.xml");

	if(eResult != XML_SUCCESS)
	{
		gErrorMsg("load config xml fail ");
		return 0;
	}
	XMLElement *pRoot = xmlDoc.RootElement();
	std::string srv_ip;
	configcommon::GetDocumentValue(pRoot,"datasvr_ip",srv_ip);
	unsigned short srv_port ;
	configcommon::GetDocumentValue(pRoot,"datasvr_port",srv_port);
return 0;
};
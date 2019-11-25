#include <sstream>
#include "LogServer.h"
using namespace zsummer::log4z;
//DECLARE_SINGLTON_MEMBER(LogServer);
//template<>
//Singleton<LogServer>::_instance = NULL;
template<>
LogServer * Singleton<LogServer>::_instance = NULL;


LoggerId Main_Id;
LoggerId Debug_Id;
LoggerId Error_Id;

bool LogServer::init(const char* szCfgPath)
{
	ILog4zManager::getRef().config(szCfgPath);

	Debug_Id = ILog4zManager::getRef().findLogger("Debug");
	Main_Id = ILog4zManager::getRef().findLogger("Main");
	Error_Id = ILog4zManager::getRef().findLogger("Error");
	if(Debug_Id == -1)
		return false;	
	printf("debug id is %d \n ",Debug_Id);
	return ILog4zManager::getInstance()->start();
}
void LogServer::fini()
{
	ILog4zManager::getInstance()->stop();
}
void LogServer::RecordLog(LoggerId id,int level,std::string log)
{
/*	if(ILog4zManager::getInstance()->prePushLog(id,level))
	{
		std::stringstream ss;
		
		ss << log;

		ILog4zManager::getInstance()->pushLog(id,level,ss.str().c_str());
	}
*/
}


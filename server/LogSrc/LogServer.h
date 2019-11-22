#ifndef LOGSERVER_H_
#define LOGSERVER_H_

#include "singleton.h"
#include "log4z.h"

extern LoggerId Debug_Id;
extern LoggerId Main_Id;
extern LoggerId Error_Id;

class LogServer : public Singleton<LogServer>
{
	public:

		LogServer(){}		

		bool init(const char* szCfgPath);
		void fini();
		void RecordLog(LoggerId id,int level,std::string log);		
	private:

};


#define g_LogSrv (* LogServer::instance())

#define gDebugMsg(log)	{LOG_DEBUG(Debug_Id,log);}
#define gErrorMsg(x) 	{LOG_ERROR(Error_Id,x);}


#endif

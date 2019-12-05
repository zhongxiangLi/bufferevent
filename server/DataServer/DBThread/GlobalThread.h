#ifndef GlobalThread_H_
#define GlobalThread_H_

#include "DBThread.h"

class GlobalThread :public DBThread
{
public:
	GlobalThread(DBInfo&dbinfo,int idx);
	virtual ~GlobalThread();
	virtual void Run();
	virtual bool OnInitDB();

	bool OnStop();

private:

};

#endif // GlobalThread_H_

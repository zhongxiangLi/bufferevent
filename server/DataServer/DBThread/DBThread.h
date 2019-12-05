

#ifndef DBThread_H_
#define DBThread_H_
#include "CommonThread.h"

#define maxsize 128
struct DBInfo
{
	char m_host[maxsize];
	char m_dbname[maxsize];
	char m_user[maxsize];
	char m_pwd[maxsize];

	int m_port;
	int m_ver;
	DBInfo()
	{
		memset(this,0,sizeof(*this));
	}

};
class DBThread :public CommonThread
{
public:
	DBThread(DBInfo &info,int idx);
	virtual ~DBThread();

	virtual void Run();
	virtual void Stop();
	virtual void CloseDB();

	void Update();
	virtual bool OnInitDB();
	
protected:
	DBInfo m_DbInfo;
	int m_ThreadIndex;
	int m_Count;

private:

};


#endif // !DBThread_H_

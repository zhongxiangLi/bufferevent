#ifndef CommonThread_H_
#define CommonThread_H_
#include <stdio.h>

#ifdef WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <WinSock2.h>
#include <process.h>
#else
#include <pthread.h>
#endif

class CommonThread
{
public:
	enum ThreadStatus
	{
		READY,
		RUNNING,
		EXITING,
		EXIT,
	};
	CommonThread();
	virtual ~CommonThread();

	virtual void Start();
	virtual	void Wait();
	virtual void Stop();
	virtual void Run();
	void		 Exit();
private:
#ifdef WIN32
	static unsigned __stdcall sThreadProc(void* param);
#else
	static void *sThreadProc(void* param);
#endif

protected:
	ThreadStatus m_status;

#ifdef  WIN32
	unsigned int m_nTID;
	HANDLE		m_hThread;
#else
	pthread_t m_nTID;
#endif //  WIN32

};
#endif // !CommonThread_H_

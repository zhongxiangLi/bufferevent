#include "CommonThread.h"

CommonThread::CommonThread()
{
	m_status = READY;
#ifdef WIN32
	m_nTID = 0;
	m_hThread = 0;
#else
	m_nTID = 0;
#endif
}

CommonThread::~CommonThread()
{
	m_status = READY;
#ifdef WIN32
	m_nTID = 0;
	m_hThread = 0;
#else
	m_nTID = 0;
#endif
}
#ifdef WIN32
 unsigned __stdcall CommonThread::sThreadProc(void* param)
{

	return 1;
}
#else
void *CommonThread::sThreadProc(void* param)
{
	return NULL;
}
#endif
void CommonThread::Start()
{
	if (m_status !=  READY)
	{
		return;
	}
#ifdef WIN32
	m_hThread = (HANDLE)_beginthreadex(NULL,0,sThreadProc,this,0,&m_nTID);
#else
	pthread_create(&m_nTID,NULL,sThreadProc,this);
#endif // WIN32
	return;
}

void CommonThread::Wait()
{

}

void CommonThread::Stop()
{

}

void CommonThread::Run()
{

}

void CommonThread::Exit()
{

}



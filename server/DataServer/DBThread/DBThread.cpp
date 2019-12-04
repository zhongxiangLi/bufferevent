
#include "DBThread.h"
DBThread::DBThread(DBInfo &info,int idx)
{
	m_DbInfo = info;
	m_ThreadIndex = idx;
	m_Count = 0;
}

DBThread::~DBThread()
{

}

void DBThread::Run()
{

}

void DBThread::Stop()
{

}

void DBThread::CloseDB()
{

}

void DBThread::Update()
{

}

bool DBThread::OnInitDB()
{
	return true;
}


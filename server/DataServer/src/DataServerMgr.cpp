
#include "DataServerMgr.h"
#include "DataLoginNetServer.h"
#include "DBThreadManager.h"
#define MODULE_DEFINE(type,name)\
		type *name = NULL;name = new type;\
		if(NULL == name){return false;}\
		if(!name->_Init())	return false;\


DataServerMgr::DataServerMgr()
{
	m_DataLoginNetServer = NULL;
}

DataServerMgr::~DataServerMgr()
{
	if (m_DataLoginNetServer != NULL)
	{
		m_DataLoginNetServer->_Exit();
		delete m_DataLoginNetServer;
		m_DataLoginNetServer = NULL;
	}
}
bool DataServerMgr::OnInit()
{
	MODULE_DEFINE(DataLoginNetServer,m_dataloginserver);
	MODULE_DEFINE(DbThreadManager,m_dbthreadmgr);
	return true;


}

void DataServerMgr::OnExit()
{
	if (m_DataLoginNetServer != NULL)
	{
		m_DataLoginNetServer->_Exit();
		delete m_DataLoginNetServer;
		m_DataLoginNetServer = NULL;
	}

}


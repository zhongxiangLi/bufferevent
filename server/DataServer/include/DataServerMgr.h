#ifndef Data_Server_Mgr_H_
#define Data_Server_Mgr_H_
#include "EventMain.h"

class DataLoginNetServer;

class  DataServerMgr :public EventMain
{
public:
	 DataServerMgr();
	~ DataServerMgr();
	virtual bool OnInit() ;
	virtual void OnExit() ;


private:
	DataLoginNetServer *m_DataLoginNetServer;

};


#endif

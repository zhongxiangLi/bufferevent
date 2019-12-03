#ifndef LoginServerMgr_h_
#define LoginServerMgr_h_

#include "EventMain.h"
#include "LoginNetServer.h"

class LoginServerMgr : public EventMain
{

public:
	LoginServerMgr();
	virtual ~LoginServerMgr();

	virtual bool OnInit();	
	virtual void OnExit();
private:


};


#endif


#ifndef EventtcpLink_h_
#define EventtcpLink_h_

#include "EventNet.h"
#include "EventSocket.h"

class EventTcpServer;
class EventTcpLink:public EventSocket
{
public:
	EventTcpLink( ){
		m_LinkId =  0;
		m_psrv = NULL;
		};
	virtual ~EventTcpLink();
	
	int GetLinkID()const{return m_LinkId;}
	void SetLinkID(int val){m_LinkId = val;}
	void SetTcpServer(EventTcpServer * srv){
		m_psrv = srv;
	}

	virtual void OnClose();
protected:

	int m_LinkId;
private:	
	EventTcpServer * m_psrv;
};

#endif
 

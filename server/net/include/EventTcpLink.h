#ifndef EventtcpLink_h_
#define EventtcpLink_h_

#include "EventNet.h"
#include "EventSocket.h"

class EventTcpLink:public EventSocket
{
public:
	EventTcpLink();
	virtual ~EventTcpLink();
	
	int GetLinkID()const{return m_LinkId;}
	void SetLinkID(int val){m_LinkId = val;}
protected:

	int m_LinkId;
private:	

};

#endif
 

#ifndef LoginNetServer_h_
#define LoginNetServer_h_

/*
	client 连接网络模块
*/

#include "EventNet.h"
#include "EventTcpServer.h"
#include "EventMain.h"

class EventTcpLink;
class LoginNetServer:public EventTcpServer
{

public:
	LoginNetServer();
	~LoginNetServer();
	//virtual bool OnInit();
	bool _OnInit();
	void _OnExit();
	//
	virtual void OnAccept(evutil_socket_t fd,struct sockaddr* adddress,int socket);

	virtual void   OnLinkClose(EventTcpLink*);
private:


};



#endif

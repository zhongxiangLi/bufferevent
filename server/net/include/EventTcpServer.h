#ifndef EVENTTCPSERVER_H_
#define EVENTTCPSERVER_H_

#include "EventSocket.h"
#include "EventMain.h"
#include "EventTcpLink.h"
using namespace std;

class EventTcpServer :public EventSocket
{
public:
public:
	EventTcpServer();
	virtual ~EventTcpServer();

	bool Listen(unsigned int port);
	static void sOnAccept(struct evconnlistener *,evutil_socket_t fd,struct sockaddr* addr,int len,void *);
	static void sOnAcceptError(struct evconnlistener *lis,void *ptr);

	//派生类继承，
	virtual EventSocket* OnAccept(evutil_socket_t fd,struct sockaddr*address,int len);
private:
	evconnlistener * m_pListener;
};

#endif

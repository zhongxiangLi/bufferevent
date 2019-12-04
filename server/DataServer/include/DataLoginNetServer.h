#ifndef Data_Login_Server_H_
#define Data_Login_Server_H_
#include "EventTcpServer.h"

class DataLoginNetServer:public EventTcpServer
{
public:
	DataLoginNetServer();
	~DataLoginNetServer();

	bool _Init();
	void _Exit();

	virtual void  OnAccept(evutil_socket_t fd,struct sockaddr*address,int len);

	virtual void   OnLinkClose(EventTcpLink*);

private:

};



#endif
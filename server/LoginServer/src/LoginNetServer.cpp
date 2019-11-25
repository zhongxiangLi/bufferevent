#include "LoginNetServer.h"
#include "log4z.h"
LoginNetServer::LoginNetServer()
{
}
LoginNetServer::~LoginNetServer()
{

}
bool LoginNetServer::_OnInit()
{

	gDebugMsg("OnInit -->");	
	size_t port  = 8897;
	Listen(port);	


	gDebugMsg("LoginNetServrt _Oninit ok");
	return true;
}
void LoginNetServer::_OnExit()
{

}
EventSocket *LoginNetServer::OnAccept(evutil_socket_t fd,struct sockaddr* address,int socket)
{
	char szIP[64] = {0};
	int port = ntohs(((struct sockaddr_in *)address)->sin_port);
	strncpy(szIP,inet_ntoa(((struct sockaddr_in*)address)->sin_addr),sizeof(szIP));

	EventTcpLink *cLink = new EventTcpLink;

	if(NULL == cLink)
	{
		gErrorMsg("Accept link is null");
		return NULL;
	}
	if(!cLink->Create(fd))
	{
		gErrorMsg("Accept link create fd error");
		return NULL;
	}
	cLink->SetIP(szIP);
	cLink->SetPort(port);
	cLink->SetExternal(true);

	gDebugMsg(" new external Accept fd is "<< fd <<"ip is "<<szIP);
	return cLink;
}

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
	if(!Listen(port))
	{
		gErrorMsg("listen on Fail");
		return false;
	}	
	gDebugMsg("LoginNetServrt _Oninit ok lsiten on "<<port);
	return true;
}
void LoginNetServer::_OnExit()
{

}
void LoginNetServer::OnAccept(evutil_socket_t fd,struct sockaddr* address,int socket)
{
	char szIP[64] = {0};
	int port = ntohs(((struct sockaddr_in *)address)->sin_port);
	strncpy(szIP,inet_ntoa(((struct sockaddr_in*)address)->sin_addr),sizeof(szIP));

	EventTcpLink *cLink = new EventTcpLink();

	if(NULL == cLink)
	{
		gErrorMsg("Accept link is null");
		return ;
	}
	if(!cLink->Create(fd))
	{
		gErrorMsg("Accept link create fd error");
		return ;
	}
	cLink->SetIP(szIP);
	cLink->SetPort(port);
	cLink->SetExternal(true);
	cLink->SetTcpServer(this);
	m_link[cLink] = cLink;
	gDebugMsg(" new external Accept fd is "<< fd <<"ip is "<<szIP);
}

void   LoginNetServer::OnLinkClose(EventTcpLink* pLink)
{
	if(pLink)
	{
		m_link.erase(pLink);
		delete pLink;
	}

}

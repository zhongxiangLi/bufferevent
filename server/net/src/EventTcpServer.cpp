#include "EventTcpServer.h"
#include "EventTcpLink.h"
#include "EventNet.h"
EventTcpServer::EventTcpServer()
{
	m_pListener = NULL;
}

EventTcpServer::~EventTcpServer()
{
	if(NULL != m_pListener)
	{
		evconnlistener_free(m_pListener);
		m_pListener = NULL;
	}

}

bool EventTcpServer::Listen(unsigned int port)
{
#ifdef WIN32
	WSADATA wsaData;
    int nRet;
    if((nRet = WSAStartup(MAKEWORD(2,2),&wsaData)) != 0){
        printf("WSAStartup failed\n");
        exit(0);
    } 
#endif
	if(0 == port)
		return false;

	 struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_port = htons(port);

    m_pListener = evconnlistener_new_bind(g_pEvMainBase, &sOnAccept, this, LEV_OPT_CLOSE_ON_FREE | LEV_OPT_REUSEABLE | LEV_OPT_THREADSAFE,
        -1, (struct sockaddr*)&sin, sizeof(sin));
    if (m_pListener == NULL)
    {
		gErrorMsg("m_pListener is NULL");
        return false;
    }

	return true;

}
void EventTcpServer::sOnAccept(struct evconnlistener *pListener, evutil_socket_t fd, struct sockaddr *address, int socklen, void *pCtx )
{
	EventTcpServer *pServer = (EventTcpServer*)pCtx;
	if(NULL == pServer)
		return ;
	//调用虚函数，派生类会实现次函数
	pServer->OnAccept(fd,address,socklen);
}
void EventTcpServer::OnAccept(evutil_socket_t fd,struct sockaddr* address,int socklen)
{

	char szIp[64]={0};
	
	unsigned int nPort = ntohs( ((struct sockaddr_in*)address)->sin_port );
	strncpy(szIp,inet_ntoa(((struct sockaddr_in*)address)->sin_addr),sizeof(szIp));

	EventTcpLink *newLink = new EventTcpLink();
	if(NULL == newLink)
		return ;
	
	if(!newLink->Create(fd))
	{
		return ;
	}	
	newLink->SetIP(szIp);
	newLink->SetPort(nPort);
	newLink->SetTcpServer(this);
	return ;

}
void EventTcpServer::sOnAcceptError(struct evconnlistener *lis,void *ptr)
{

}

void EventTcpServer::OnLinkClose(EventTcpLink* pLink)
{
	gErrorMsg("OnLinkClose ");
	if(pLink)
	{
		m_link.erase(pLink);
		delete pLink;
	}

}

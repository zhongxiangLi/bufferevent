#include "EventTcpServer.h"
#include "EventTcpLink.h"

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
	if(0 == port)
		return false;
	struct sockaddr_in addr;

	memset(&addr,0,sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(port);
	/*
		struct event_base * g_pEvMainBase,evconnlistener_cb cb  
		,void *ptr,unsigned flags,int backlog,const struct *sa,int socklen
		return: struct evconnlistener*
	----------------------------------
		cb typedef void(*evconnlistener_cb)(struct evconnlistener *listener,evutil_socket_t socket,struct sockaddr*addr,int len,void *ptr)
	*/
	m_pListener = evconnlistener_new_bind(g_pEvMainBase,&sOnAccept,this,LEV_OPT_CLOSE_ON_FREE| LEV_OPT_REUSEABLE | LEV_OPT_THREADSAFE,-1,(struct sockaddr *)&addr,sizeof(addr));
	
	if(NULL == m_pListener)
		return false;

	m_nSocket = evconnlistener_get_fd(m_pListener);
	/*
		typedef void (*evconnlistener_errorcb)(struct evconnlistener *lis,void *ptr);
	*/
	gDebugMsg("listen on "<<port);
	evconnlistener_set_error_cb(m_pListener,&sOnAcceptError);
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
EventSocket * EventTcpServer::OnAccept(evutil_socket_t fd,struct sockaddr* address,int socklen)
{

	char szIp[64]={0};
	
	unsigned int nPort = ntohs( ((struct sockaddr_in*)address)->sin_port );
	strncpy(szIp,inet_ntoa(((struct sockaddr_in*)address)->sin_addr),sizeof(szIp));

	EventTcpLink *newLink = new EventTcpLink();
	if(NULL == newLink)
		return NULL;
	
	if(!newLink->Create(fd))
	{
		return NULL;
	}	
	newLink->SetIP(szIp);
	newLink->SetPort(nPort);

	return newLink;

}
void EventTcpServer::sOnAcceptError(struct evconnlistener *lis,void *ptr)
{

}

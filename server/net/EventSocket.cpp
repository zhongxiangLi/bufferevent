#include "EventSocket.h"
#include "LogServer.h"
#include "EventMain.h"


EventSocket::EventSocket()
{
	m_nSocket = 0;
	m_pBuffev = NULL ;
	m_isExternal = false;
	
}
EventSocket::~EventSocket()
{
	if(m_pBuffev != NULL)
	{
		bufferevent_free(m_pBuffev);
		m_pBuffev = NULL;
	}
	if(m_pTick)
	{
		m_pTick = false;
		event_del(&m_tickEv);
	}
}

bool EventSocket::InitTick(int sec,int ms)
{
	struct timeval tv;
	tv.tv_sec = sec;
	tv.tv_usec = ms*1000;
	
	event_assign(&m_tickEv,g_pEvMainBase,-1,EV_PERSIST,&EventSocket::onTickCB,(void*)this);
	
	event_add(&m_tickEv,&tv);
	
	m_pTick = true;
	
	return true;
	
}
bool EventSocket::Create(evutil_socket_t nfd)
{
	if(NULL != m_pBuffev || m_nSocket > 0)
	{
		return true;
	}
	if(nfd == 0)
		m_nSocket = -1;
	else
		m_nSocket = nfd;
	gDebugMsg("socket fd is "<< m_nSocket);	
	m_pBuffev = bufferevent_socket_new(g_pEvMainBase,m_nSocket,BEV_OPT_CLOSE_ON_FREE);
	if(m_pBuffev == NULL)
	{
		int err = EVUTIL_SOCKET_ERROR();
		gErrorMsg(err <<" "<<evutil_socket_error_to_string(err));
		return false;	
	}
	gDebugMsg("bufferevent_socket_new success");
	if(nfd == 0)
		m_nSocket = bufferevent_getfd(m_pBuffev);
	
	bufferevent_setcb(m_pBuffev,&EventSocket::sOnRead,&EventSocket::sOnWrite,&EventSocket::sOnEvent,(void*)this);
	bufferevent_enable(m_pBuffev,EV_READ|EV_WRITE);
	
	//设置非延时
	//int bOptVal =1;
	//int nOptLen = sizeof(int);
	//setsockopt(m_nSocket,IPPROTO_TCP,TCP_NODELAY,(const char*)&bOptVal,nOptLen);
	
	//设置缓冲区大小
	int buf = 1024*1024;
	setsockopt(m_nSocket,SOL_SOCKET,SO_RCVBUF,(const char *)&buf,sizeof(int));
	setsockopt(m_nSocket,SOL_SOCKET,SO_SNDBUF,(const char*)&buf,sizeof(int));
	return true;
	
}
void EventSocket::sOnRead(struct bufferevent* pBev,void *pData)
{
	// 测试：简单把客户端发送过来的数据解析 输出然后发出去
	/*
		正常需要在这进行消息的解析操作
	*/
	gErrorMsg("read new msg");
	// 从缓冲区读取到evbuffer中
	struct evbuffer *buf = evbuffer_new();
	bufferevent_read_buffer(pBev,buf);
	int len = evbuffer_get_length(buf);

	char  data[1024];
	memset(data,0,sizeof(data));
	evbuffer_remove(buf,data,len);
	gDebugMsg("read msg len is "<<len<<" data is "<<data);	
	evbuffer_free(buf);
	
	bufferevent_write(pBev,(void*)data,len);
	
}
void EventSocket::sOnWrite(struct bufferevent* pBev,void *pData)
{
	//此函数会在发送之后 回调到，不用写任何逻辑
	//gErrorMsg(" have Write");
}
void EventSocket::sOnEvent(struct bufferevent* pBev,short events,void *pData)
{
	gErrorMsg(" Event have ");
}
void EventSocket::onTickCB(evutil_socket_t fd ,short event,void *pData)
{
		gErrorMsg(" have onTickCB");
	
}

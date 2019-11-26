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
void EventSocket::sOnRead(struct bufferevent* pBev,void *pData)	// 静态函数
{
	// 测试：简单把客户端发送过来的数据解析 输出然后发出去
	/*
		正常需要在这进行消息的解析操作
	*/
	EventSocket *pSocket = (EventSocket*)pData;
//	bufferevent_read_buffer(m_peve);

	gErrorMsg("read new msg");
	// 从缓冲区读取到evbuffer中
	struct evbuffer *buf = evbuffer_new();
	bufferevent_read_buffer(pBev,buf);
	//查找包头标识
	do{
		short flags = 0;
		int len = evbuffer_get_length(buf);
		if(len < sizeof(short)) //包头标识 0x55AA 占用两个字节
			return;
		
		evbuffer_copyout(buf,(void*)&flags,sizeof(short));//从evbuffer中拷贝2个字节出来
		if(flags == PACKET_HEAD) //0x55AA
			break;
		else
			evbuffer_drain(buf,1);//包头标识匹配不上  删除一个字节
	}while(1);
	//解析包头数据
	size_t headLen  = 0;
	EventNetPacket	m_head;
	memset(&m_head,0,sizeof(m_head));

	if(pSocket->IsExternal())
		headLen = sizeof(EventClientPacket);
	else
		headLen = sizeof(EventNetPacket);

	if(evbuffer_get_length(buf) < headLen)
		return;
	//获取包头数据
	evbuffer_remove(buf,(void*)&m_head,headLen);

	//获取包体数据
	evbuffer* m_body = evbuffer_new();
	evbuffer_remove_buffer(buf,m_body,m_head.m_i2DataSize);
	
	size_t head_len = sizeof(EventNetPacket);
	size_t pack_len = head_len + m_head.m_i2DataSize;

	EventNetPacket* pPacket = (EventNetPacket*)malloc(pack_len);
	memcpy(pPacket,&m_head,head_len);

	evbuffer_remove(m_body,(void*)(pPacket->m_szData),m_head.m_i2DataSize);

	//  分发数据到具体协议


	
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
void EventSocket::Send(const char* buf,const int nSize)
{
	bufferevent_write(m_pBuffev,(void*)buf,nSize);
}
int EventSocket::SendNetMsg(EventNetPacket* pMsg)
{
	if(NULL == pMsg)
	{
		gErrorMsg("SendNetMsg msg is NULL");
		return -1;
	}
	int msgSize  = 0;
	if(!IsExternal())
	{
		pMsg->m_i4SrvID = 1;
		msgSize = pMsg->m_i2DataSize + sizeof(EventNetPacket);
		Send((char*)pMsg,msgSize);
	}else
	{
	}


	return 0;
}

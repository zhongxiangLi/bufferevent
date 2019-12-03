#include <event2/event.h>
#include <event2/bufferevent.h>
#include <iostream>
#include "test.pb.h"
#include "test.pb.cc"
#include <arpa/inet.h> 
#include <sys/stat.h>
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/socket.h>   //connect,send,recv,setsockopt等
#include <sys/types.h>      
#include <netinet/tcp.h>
#include <netinet/in.h>     // sockaddr_in, "man 7 ip" ,htons
#include <poll.h>             //poll,pollfd
#include <arpa/inet.h>   //inet_addr,inet_aton
#include <unistd.h>        //read,write
#include <netdb.h>         //gethostbyname



using namespace std;
const char* szip = "192.168.2.48";
int port = 8897;


struct event_base*	g_eventbase = NULL;
struct bufferevent* m_evBuffer = NULL;


static void     sOnRead(struct bufferevent *pBev, void *pData);
static void     sOnWrite(struct bufferevent *pBev, void *pData);
static void     sOnEvent(struct bufferevent *pBev, short events, void *pData);

typedef struct _packet_base_st
{
	short       m_i2Begin;
	short       m_i2PacketID;
	long long   m_i8Guid;           // 玩家GUID
	int			m_i2DataSize;
	int			m_i4Compress;
	short		m_i4SrvID;			// server id

	char        m_szData[0];
	_packet_base_st() 
	{
	//	memset(this, 0, sizeof(*this));
	}
}EventNetPacket;

static void     sOnRead(struct bufferevent *pBev, void *pData){
	std::cout <<"OnRead"<<std::endl;
}
static void     sOnWrite(struct bufferevent *pBev, void *pData){
	std::cout <<"OnWrite"<<std::endl;
}
static void     sOnEvent(struct bufferevent *pBev, short events, void *pData){
	std::cout <<"sOnEvent"<<std::endl;

	if(events & BEV_EVENT_CONNECTED)
	{
		std::cout <<"connect ok"<<std::endl;
	}else if(events & (BEV_EVENT_ERROR|BEV_EVENT_EOF))
	{
		struct event *base = (struct event*)pData;
		if(events & BEV_EVENT_ERROR)
		{
			int err = bufferevent_socket_get_dns_error(pBev);
			if(err)
				std::cout <<"dns error"<<std::endl;
		}	
		std::cout <<"Closing"<<std::endl;
		bufferevent_free(pBev);
		event_free(base);
	}
}
void cmd_msg_cb(int fd,short events,void* arg)
{
	char msg1[1024];
	int ret = read(fd,msg1,sizeof(msg1));
	if(ret < 0)
	{
		return ;
	}
	EventNetPacket msg;
	msg.m_i2Begin = 0x55AA;
	msg.m_i2PacketID = 1;
	msg.m_i8Guid = 0;
	msg.m_i2DataSize = 2;
	msg.m_i4Compress =1;
	msg.m_i4SrvID = 1;

	char buf[1024] ={0};
	memcpy(buf,(char*)&msg,sizeof(msg));

	struct bufferevent*bev = (struct bufferevent*)arg;
	bufferevent_write(bev,(void*)buf,sizeof(msg));
}
int main()
{


	int m_socket = -1;
	struct event_config* cfg = event_config_new();

	g_eventbase = event_base_new_with_config(cfg);

	//m_socket -1 表示客户端需要用bufferevent_socket_connect 连接服务器	
	m_evBuffer = bufferevent_socket_new(g_eventbase,m_socket,BEV_OPT_CLOSE_ON_FREE);
	
//	监听终端输入事件
	struct event* ev_cmd = event_new(g_eventbase,STDIN_FILENO,EV_READ|EV_PERSIST,cmd_msg_cb,(void*)m_evBuffer);

	event_add(ev_cmd,NULL);

	//创建socket连接
	m_socket = bufferevent_getfd(m_evBuffer);

	bufferevent_setcb(m_evBuffer,&sOnRead,&sOnWrite,&sOnEvent,(void*)ev_cmd);

	bufferevent_enable(m_evBuffer,EV_READ|EV_WRITE);

	if(	bufferevent_socket_connect_hostname(m_evBuffer,NULL,AF_INET,szip,port) == -1)
	{
		std::cout <<"Error connect "<<endl;
		return -1;
	}
	event_base_dispatch(g_eventbase);
	std::cout <<"onconnect suddccess"<<std::endl;	

	event_base_free(g_eventbase);

	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "common.h"

reactor::Reactor g_reactor;


//const size_t kBufferSize = 1024;

//char g_read_buffer[kBufferSize];
//char g_write_buffer[kBufferSize];

class TimeClient :public reactor::EventHandler
{
public:
	TimeClient();
	~TimeClient();
	bool connectToServer(const char* ip,unsigned short port);
	virtual reactor::handle_t GetHandle()const;

	virtual void HandleRead();

	virtual void HandleWrite();
	
	virtual void HandleError();
private:
	reactor::handle_t m_handle;


};

TimeClient::TimeClient():EventHandler()
{
	m_handle = ::socket(AF_INET,SOCK_STREAM,0);
}
bool TimeClient::connectToServer(const char* ip,unsigned short port)
{
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(ip);
	
	if(connect(m_handle,(struct sockaddr*)&addr,sizeof(addr)) < 0)
		return false;
	return true;

}
reactor::handle_t TimeClient::GetHandle() const
{
	return m_handle;
}
void TimeClient::HandleRead()
{
	memset(g_read_buffer,0,kBufferSize);
	int 
	len = recv(m_handle,g_read_buffer,kBufferSize,0);
	if(len > 0)
	{
		fprintf(stderr,"%s",g_read_buffer);
		g_reactor.RegisterHandler(this,reactor::kReadEvent);
	}
}
void TimeClient::HandleWrite()
{
	memset(g_write_buffer,0,kBufferSize);
	int len = sprintf(g_write_buffer,"timer\r\n");
	len = send(m_handle,g_write_buffer,len,0);
	if(len > 0)
	{
		fprintf(stderr,"%s",g_write_buffer);
		g_reactor.RegisterHandler(this,reactor::kReadEvent);
	}
}
void TimeClient::HandleError()
{
	fprintf(stderr,"server close\n");
	close(m_handle);
	exit(0);
}
TimeClient::~TimeClient()
{
	close(m_handle);
}
int main(int argc,char * argv[])
{
	if(argc < 3)
	{
		fprintf(stderr,"usgae:%s ip port\n",argv[0]);
		return 0;
	}
	TimeClient client;
	if(!client.connectToServer(argv[1],atoi(argv[2])));
	{
		fprintf(stderr,"connect server fail\n");
		return 0;
	}
	g_reactor.RegisterHandler(&client,reactor::kWriteEvent);
	while(1)
	{
		g_reactor.HandleEvents();
		sleep(1);
	}

	g_reactor.RemoveHandler(&client);
	return 0;
}

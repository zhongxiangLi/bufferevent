#include "DataLoginNetServer.h"
#include "common.h"
#include "LogServer.h"
#include "EventTcpLink.h"

DataLoginNetServer::DataLoginNetServer()
{

}

DataLoginNetServer::~DataLoginNetServer()
{

}

bool DataLoginNetServer::_Init()
{
	unsigned int port = 8890;
	if (!Listen(port))
	{
		return false;
	}
	return true;
}

void DataLoginNetServer::_Exit()
{

}

void DataLoginNetServer::OnAccept(evutil_socket_t fd,struct sockaddr*address,int len)
{
	//�յ��µ�����

}

void DataLoginNetServer::OnLinkClose(EventTcpLink*)
{
	//���ӹر�

}

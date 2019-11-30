
#include "EventTcpLink.h"
#include "EventTcpServer.h"

EventTcpLink::~EventTcpLink()
{
	m_psrv = NULL;
}
void EventTcpLink::OnClose()
{
	EventSocket::OnClose();
	if(NULL !=m_psrv)
		m_psrv->OnLinkClose(this);
}
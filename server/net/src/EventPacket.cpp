#include "EventPacket.h"
#include "stdlib.h"
#include "NET_MSG_DEF.h"
#include "CS_NET_MSG_STRUCT.h"
int* EventPacket::m_sMsgSize = NULL;

EventPacket::EventPacket()
{

}

EventPacket::~EventPacket()
{

}
void EventPacket::sInit()
{
	if(NULL == m_sMsgSize)
	{
		m_sMsgSize = new int[Msg_Type_Max];
		memset(m_sMsgSize,0,Msg_Type_Max*sizeof(int));
	}
	m_sMsgSize[CS_Msg_Min] = 0;
#define _NET_MSG_DEF(type,n)	m_sMsgSize[type] = sizeof(_##type);
	#include "CS_NET_MSG_DEF.h"

}

bool EventPacket::InitFromMsgType(short nPackID)
{
	if(nPackID >= Msg_Type_Max || NULL == m_sMsgSize )
		return false;
//	int nBodySize
	
	return true;
}

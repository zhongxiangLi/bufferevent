#include "EventPacket.h"
#include "stdlib.h"
#include "NET_MSG_DEF.h"
#include "CS_NET_MSG_STRUCT.h"
#include "EventNet.h"

int* EventPacket::m_sMsgSize = NULL;

EventPacket::EventPacket()
{
	m_nPacketLen = 0;
	m_nPacketBuff = NULL;
}

EventPacket::~EventPacket()
{
	if(NULL != m_nPacketBuff)
	{
		free(m_nPacketBuff);
		m_nPacketBuff = NULL;
	}
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
	int nBodySize = m_sMsgSize[nPackID];
	if(nBodySize <= 0)
		return false;
	if(nBodySize >= PACKET_BODY_MAX)
	{	
		//rrorMsg("InitFromMsgType packID "<<nPackID<<" bodySize "<<nBodySize);
		return false;
	}
	if(m_nPacketBuff)
	{
		free(m_nPacketBuff);
		m_nPacketBuff = NULL;
	}
	m_nPacketBuff = (char*)calloc(1,nBodySize+sizeof(EventNetPacket));
	EventNetPacket * pHeader = GetHeader(); // (EventNwtPacket*)m_nPacketBuff
	pHeader->m_i2PacketID = nPackID;
	pHeader->m_i2Begin = PACKET_HEAD;
	pHeader->m_i2DataSize = nBodySize;
	pHeader->m_i8Guid = 0;
	
	m_nPacketLen =  sizeof(EventNetPacket) + nBodySize;
	memset(pHeader->m_szData,0,nBodySize);
	return true;
}

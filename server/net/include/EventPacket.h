/*
  通信协议设计

*/

#ifndef EventPacket_h_
#define EventPacket_h_

#include <string.h>
#include <stdlib.h>
typedef struct _package_client_
{
	short m_i2Begin;
	short m_i2PacketID;
	long long m_i8Guid;
	int	m_i2DataSize;
	int	m_i4Compress;
	char m_szData[0];
	_package_client_()
	{
		memset(this,0,sizeof(*this));
	}

}EventClientPacket;

class EventPacket
{
public:
	EventPacket();
	~EventPacket();
	static void sInit();
	static int *m_sMsgSize;
	
	bool	InitFromMsgType(short nPackId);
private:
	int	m_nPacketLen;
	char *m_nPacketBuff;
};

#endif

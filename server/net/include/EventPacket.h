/*
  通信协议设计 网络包 包头数据

*/

#ifndef EventPacket_h_
#define EventPacket_h_
#define PACKET_HEAD		(0x55AA)	//网络包头标识
#define PACKET_BODY_MAX (0x7FFFFFFF)
#include <string.h>
#include <stdlib.h>

#ifdef _MSC_VER
#pragma warning (disable: 4200)
#endif
#pragma pack(push,1)
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

typedef struct _packet_base_st
{
	short       m_i2Begin;
	short       m_i2PacketID;
	long long   m_i8Guid;           // 玩家GUID
	int			m_i2DataSize;
	int			m_i4Compress;
#ifdef NEED_ENCRYPT
	short		m_i2Encrypt;		//  是否加密
#endif // NEED_ENCRYPT
	short		m_i4SrvID;			// server id

	char        m_szData[0];
	_packet_base_st() 
	{
		memset(this, 0, sizeof(*this));
	}
}EventNetPacket;

class EventPacket
{
public:
	EventPacket();
	~EventPacket();
	static void sInit();
	static int *m_sMsgSize;
	
	bool	InitFromMsgType(short nPackId);
	EventNetPacket *GetHeader() {return (EventNetPacket*)m_nPacketBuff;}
	char* 			GetBody(){return m_nPacketBuff+sizeof(EventNetPacket);}
	inline int		GetPacketLen(){return m_nPacketLen;}
private:
	int	m_nPacketLen;
	char *m_nPacketBuff;
};

#endif

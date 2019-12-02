#ifndef EVENTSOCKET_H_
#define EVENTSOCKET_H_

#include "EventNet.h"
#include "EventPacket.h"

class EventSocket{
	
	public:
		//函数指针原型 void (*)(EventSocket *pScoket,void *pData) , 含参数返回值void
		// fpOnCloseCB 函数指针的别名
		typedef void (* fpOnCloseCB)(EventSocket *pScoket,void *pData);
	public:
		EventSocket();
		
		virtual ~EventSocket();
		
		bool InitTick(int sec,int ms);
		
		bool Create(evutil_socket_t nFd = 0);
	public:
		static void sOnRead(struct bufferevent* pBev,void *pData);
		static void sOnWrite(struct bufferevent* pBev,void *pData);
		static void sOnEvent(struct bufferevent* pBev,short events,void *pData);
		
		int         GetPort() const      { return m_Port; }
		void        SetPort(int val)     { m_Port = val; }
		std::string GetIP() const        { return m_strIP; }
		void        SetIP(std::string val) { m_strIP = val; }	

		bool 		IsExternal(){return m_isExternal;}
		void		SetExternal(bool val){m_isExternal = val;}

		int 		SendNetMsg(EventNetPacket* pMsg);
		void		Send(const char* buf,const int szie);

		virtual	void OnClose();
	protected:

		static void onTickCB(evutil_socket_t ,short ,void *);
		fpOnCloseCB m_fnOnClose;
		
		evutil_socket_t		m_sockfd;
		struct bufferevent*	m_pBuffev;
	
		int 			m_Port;
		std::string 	m_strIP;
		
		struct event 	m_tickEv;
		bool 			m_pTick;
		bool			m_isExternal; //内部连接false和外部连接true
};

#endif

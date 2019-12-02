#ifndef EVENTMAIN_H_
#define EVENTMAIN_H_
#include "EventNet.h"
#include <list>
#include <string>
using namespace std;

class EventMain
 {
	 public:
		EventMain();
		virtual ~EventMain();
		virtual void Run(int argc,char *argv[],int nFPS =1);
		virtual bool OnInit() = 0;
		virtual bool Init();


		void	sInitSignal();
		void	Stop();
		void	Crash(int);
		bool	IsRunning(){return m_bRunning;}

		static	void sSignalProcess(int nSig);
		static void sOnAccept(struct evconnlistener *,evutil_socket_t fd,struct sockaddr* addr,int len,void *);
		
	 private:
	 
		bool m_bRunning;	

 };
extern struct event_base *g_pEvMainBase;
#endif

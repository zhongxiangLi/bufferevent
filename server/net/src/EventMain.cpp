#include "EventMain.h"
#include "EventSocket.h"
#include "EventNet.h"
#include "EventPacket.h"

struct event_base *g_pEvMainBase =  NULL;

EventMain *g_pEventMain = NULL;
EventMain::EventMain()
{
	if(NULL != g_pEventMain)
	{
		gErrorMsg("EventMain");
		assert(0);
	}
	m_bRunning = true;
	g_pEventMain = this;
}
EventMain::~EventMain(){
	
}
void EventMain::Run(int argc,char *argv[],int nFPS )
{
	EventPacket::sInit();
	//注册信号事件
	sInitSignal();

	//初始化 系统module
	if(!OnInit())
	{
		return ;
	}
	gDebugMsg("init ok");
	//初始化 timer
	//游戏主循环
	while(IsRunning())
	{
		event_base_loop(g_pEvMainBase,EVLOOP_NONBLOCK);
	}
	//
	return ;
}
bool EventMain::Init()
{
	struct event_config* cfg = event_config_new();
	if(NULL == cfg)
	{
		gErrorMsg("cfg is NULL");
		return false;
	}
	g_pEvMainBase = event_base_new_with_config(cfg);
	if(NULL == g_pEvMainBase)
	{
		gErrorMsg("g_pEvMainBase");
		event_config_free(cfg);
		return false;
	}
	event_config_free(cfg);
	gDebugMsg("event_base new end-->");
	return true;
}
void EventMain::sOnAccept(struct evconnlistener *pListener, evutil_socket_t fd, struct sockaddr *address, int socklen, void *pCtx )
{
}

void EventMain::sInitSignal()
{
	signal(SIGFPE,SIG_IGN);
	signal(SIGINT, sSignalProcess);
	signal(SIGTERM, sSignalProcess);

    signal(SIGILL, sSignalProcess);
	signal(SIGSEGV, sSignalProcess);
	signal(SIGABRT, sSignalProcess);
	
	//signal(SIGBREAK,sSignalProcess);
	
}
void EventMain::sSignalProcess(int nSig)
{
	switch(nSig)
	{
		case SIGINT:
		case SIGTERM:
		//case SIGBREAK:
		{
			g_pEventMain->Stop();
		}break;
		case SIGILL:
		case SIGSEGV:
		case SIGABRT:
		default:
		{
			g_pEventMain->Crash(nSig);
		}break;
		
	}
}

void EventMain::Stop()
{
	m_bRunning = false;
}
void EventMain::Crash(int)
{
	//g_LogSrv.fini();
	
}

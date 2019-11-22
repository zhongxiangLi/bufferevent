#include "EventMain.h"
#include "EventSocket.h"
#include "LogServer.h"
struct event_base *g_pEvMainBase =  NULL;

EventMain *g_pEventMain = NULL;
EventMain::EventMain()
{
	if(NULL != g_pEventMain)
	{
		assert(0);
	}
	m_bRunning = true;
	g_pEventMain = this;
}
EventMain::~EventMain(){
	
}
void EventMain::Run(int argc,char *argv[],int nFPS )
{
	//注册信号事件
	sInitSignal();
	//注册 系统module
	OnRegister();	
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
bool EventMain::OnInit()
{
	// 分配一个event_config
	struct event_config *cfg = event_config_new();
	//不使用不能提供所有指定特征的后端 EV_FEATURE_ET 要求支持边缘触发
	if(event_config_require_features(cfg,EV_FEATURE_ET) == -1)
	{
		gErrorMsg("*************************");
	}
	//在创建event_base时 设置一个或者更多个下面的运行标志
	event_config_set_flag(cfg,EVENT_BASE_FLAG_EPOLL_USE_CHANGELIST);
#ifdef EVENT_USE_THREAD
	evthread_use_pthreads();
#endif

	g_pEvMainBase = event_base_new_with_config(cfg);
	if(NULL == g_pEvMainBase)
	{
		event_config_free(cfg);
		exit(1);
	}
	gDebugMsg("event_base new end-->");
	//初始化Module
	INIT_FUNC_LIST::iterator iter = m_listInitFunc.begin();

	for(; iter != m_listInitFunc.end();++iter)
	{
		OnInitFunc pFn = *iter;
		if(pFn)
		{
			string name;
			bool ret = (*pFn)(NULL,name);
			gDebugMsg("name is "<<name<<" -->");	
			if(!ret)
			{
				gErrorMsg(name << "Init Error");
				return false;
			}
	
		}

	}
	event_config_free(cfg);
	return true;
}
void EventMain::RegisterModule(OnInitFunc fpOninit,OnExitFunc fpOnExit)
{
	gDebugMsg("init "<<fpOninit);
	if(fpOninit)
		m_listInitFunc.push_back(fpOninit);
	if(fpOnExit)
		m_listExitFunc.push_back(fpOnExit);
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

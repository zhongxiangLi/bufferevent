#ifndef EVENTMAIN_H_
#define EVENTMAIN_H_
#include "EventNet.h"
#include <list>
#include <string>
using namespace std;

//typedef bool(*OnInitFunc)(void *arg,std::string&retName);
//typedef void(*OnExitFunc)(void *arg);

typedef bool (* OnInitFunc)();
typedef void (* OnExitFunc)();
 
class EventMain
 {
	 public:
		EventMain();
		virtual ~EventMain();
		virtual void Run(int argc,char *argv[],int nFPS =1);
		
		
		void sInitSignal();
		static	void sSignalProcess(int nSig);
		void Stop();
		void Crash(int);
				
		bool OnInit();
		void re(void(*)());
		//void RegisterModule(OnInitFunc fpOninit,OnExitFunc fpOnExit);
		void            RegisterMoudle(OnInitFunc fpOninit, OnExitFunc fpOnExit);
		virtual void OnRegister() = 0;
		
		bool IsRunning(){return m_bRunning;}
	 private:
	 
		bool m_bRunning;
		
	    typedef list <OnInitFunc> INIT_FUNC_LIST;		
	    typedef list <OnExitFunc> EXIT_FUNC_LIST;		

    	INIT_FUNC_LIST  m_listInitFunc;			//初始化函数回调
	    EXIT_FUNC_LIST  m_listExitFunc;			//退出函
	//	typedef	list<OnInitFunc> INIT_FUNC_LIST ;
	//	typedef list<OnExitFunc> EXIT_FUNC_LIST ;
	
	//	INIT_FUNC_LIST m_listInitFunc;
	//	EXIT_FUNC_LIST m_listExitFunc;

		

 };
extern struct event_base *g_pEvMainBase;
#endif

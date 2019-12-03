#include "LoginServerMgr.h"
#include "LoginNetServer.h"



LoginNetServer *g_LoginNetSrv = NULL;

LoginServerMgr::LoginServerMgr()
{

}

LoginServerMgr::~LoginServerMgr()
{

}
bool LoginServerMgr::OnInit(){

	Init();

	if ( g_LoginNetSrv != NULL)
		return false;
	g_LoginNetSrv = new LoginNetServer;
	return g_LoginNetSrv->_OnInit();
}

void LoginServerMgr::OnExit()
{
	if(g_LoginNetSrv)
	{
		g_LoginNetSrv->_OnExit();
		//
		free(g_LoginNetSrv);
		g_LoginNetSrv = NULL;
		}
}


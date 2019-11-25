#include "LoginServerMgr.h"
#include "LoginNetServer.h"



LoginNetServer *g_LoginNetSrv = NULL;
bool _LoginNetServer_OnInit()
{
  if ( g_LoginNetSrv != NULL)
     return false;
  g_LoginNetSrv = new LoginNetServer;
 return g_LoginNetSrv->_OnInit();
}
void _LoginNetServer_OnExit() 
{
    g_LoginNetSrv->_OnExit();
	//
	free(g_LoginNetSrv);
	g_LoginNetSrv = NULL;
}


//G_MOUDLE_DEFINITION(LoginNetServer, g_LoginNetSrv);
LoginServerMgr::LoginServerMgr()
{

}

LoginServerMgr::~LoginServerMgr()
{

}
void LoginServerMgr::OnRegister()
{
	//G_MOUDLE_REGISTER(LoginNetServer);
	RegisterMoudle(_LoginNetServer_OnInit,_LoginNetServer_OnExit);	
}

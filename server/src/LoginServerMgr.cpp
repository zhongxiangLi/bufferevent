#include "LoginServerMgr.h"
#include "LoginNetServer.h"

LoginNetServer *g_LoginNetSrv = NULL;
bool _LoginNetServer_OnInit(void *arg, string &name)
{
   name = "LoginNetServer";
  if ( g_LoginNetSrv != NULL)
     return false;
  g_LoginNetSrv = new LoginNetServer;
  //  gSystemStream("MOUDLE INIT " << #type);
 return g_LoginNetSrv->_OnInit();
}
void _LoginNetServer_OnExit(void *arg) 
{
 //  gSystemStream("MOUDLE EXIT " << LoginNetServer);
    g_LoginNetSrv->_OnExit();
   // SAFE_DELETE(g_LoginNetSrv);
}


LoginServerMgr::LoginServerMgr()
{

}

LoginServerMgr::~LoginServerMgr()
{

}
void LoginServerMgr::OnRegister()
{
	RegisterModule(_LoginNetServer_OnInit,_LoginNetServer_OnExit);	
}

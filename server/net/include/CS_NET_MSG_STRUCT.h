/*
	通信协议结构体
*/
#ifndef NETMSGSTRUCT_H_
#define NETMSGSTRUCT_H_

struct _CS_Login
{
	_CS_Login()
	{
		memset(this,0,sizeof(*this));	
	}
	char *m_account[33];
	
};

#endif

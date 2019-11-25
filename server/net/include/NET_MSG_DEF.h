
/*
	消息定义
*/
#ifndef NETMSGDEF_H_
#define NETMSGDEF_H_

enum	Net_Msg_Type
{
	CS_Msg_Min  = 1000,
#define _NET_MSG_DEF(type,id)	type = id,
	#include "CS_NET_MSG_DEF.h"	
	CS_Msg_Max  = 2000,	 
	Msg_Type_Max = 4000,

};
#endif

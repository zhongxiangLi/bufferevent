#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include "singleton.h"


class Global: public Singleton<Global>
{
	public:
		Global();
		~Global();


};

#endif

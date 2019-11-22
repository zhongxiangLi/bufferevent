#ifndef __SINGLETON_H_
#define __SINGLETON_H_
#include <stdio.h>

template<class T>
class Singleton{
	
public:
	static inline T*instance();
	void release();
protected:
	Singleton(void){}
	~Singleton(void){}
	static T* _instance;

};

template<class T>
inline T * Singleton<T>::instance()
{
	if(!_instance)
		_instance = new T;
	return _instance;	
}
template<class T>
void Singleton<T>::release()
{
	if(!_instance)
		return;
	delete _instance;
	_instance = 0;
}
//template<class T>
//T* Singleton<T>::_instance = NULL;

//宏定义 类模板的特化
#define DECLARE_SINGLTON_MEMBER(SubClass)\
	template<>\
	SubClass  * Singleton<SubClass>::_instance = NULL;
#endif

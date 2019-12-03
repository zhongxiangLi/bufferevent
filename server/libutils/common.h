#ifndef REACTOR_TEST_COMMON_H_
#define REACTOR_TEST_COMMON_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <errno.h>
//namespace Config{
#include <errno.h>




typedef int handle_t;
typedef unsigned int event_t;
 

#include <string>
#include <sstream>
#include"tinyxml2.h"
using namespace tinyxml2;

namespace configcommon{

template<class T>
bool StringToBaseType(const std::string& str ,T &val){
	std::istringstream stream;
	stream.str(str);
	if (stream>>val) return true;

	return false;

}

template<class T>
 bool GetNodeValue(tinyxml2::XMLElement *el,T& val){
	if (!el) return false;
	if (!el->FirstChild() || StringToBaseType(el->FirstChild()->Value(),val))
		return false;
	return true;
}


template<class T>
static bool GetDocumentValue(tinyxml2::XMLElement *xmldoc,const std::string & name,T& val){

	if (!xmldoc) return false;

	XMLElement *pValue = xmldoc->FirstChildElement(name.c_str());
	if (!pValue) return false;

	return GetNodeValue(pValue,val);
	
}




}


#endif

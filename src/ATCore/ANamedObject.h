
#ifndef ATCore_ANamedObject_h
#define ATCore_ANamedObject_h

#include "config.h"
#include <string>

//Everithing, that has name
class AT_CORE_API ANamedObject
{
public:
	ANamedObject(const std::string & _name = "");
	void setName(const std::string & _name);
	const char * name();
	bool nameIs(const char * _name);
private:
	std::string m_pName;
};

//typedef USAbstractNamedObject<int> USIdentifiableObject;
#endif

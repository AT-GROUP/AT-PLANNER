
#ifndef ATCore_ANamedObject_h
#define ATCore_ANamedObject_h

#include "config.h"
#include "AError.h"
#include <string>

struct _xmlNode;

//Everithing, that has name
class AT_CORE_API ANamedObject
{
public:
	ANamedObject(const std::string & _name = "");
	void setName(const std::string & _name);
	const std::string & name() const;
	bool nameIs(const char * _name);
	virtual AError deserialize(_xmlNode * doc_node);
private:
	std::string m_pName;
};

//typedef USAbstractNamedObject<int> USIdentifiableObject;
#endif

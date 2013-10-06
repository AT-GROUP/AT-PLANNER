
#ifndef ATEnvironment_ANamedObject_h
#define ATEnvironment_ANamedObject_h

#include <string>

//Everithing, that has name
class ANamedObject
{
public:
	ANamedObject(const char * c_name = "");
	~ANamedObject();
	void setName(const char * _name);
	const char * name();
	bool nameIs(const char * _name);
private:
	char * m_pName;
};

//typedef USAbstractNamedObject<int> USIdentifiableObject;
#endif

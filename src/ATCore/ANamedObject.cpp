#include "ANamedObject.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

using namespace std;

ANamedObject::ANamedObject(const std::string & _name)
	:m_pName(_name)
{
}


const std::string & ANamedObject::name() const
{
	return m_pName;
}

bool ANamedObject::nameIs(const char * _name)
{
	return !strcmp(name().c_str(), _name);
}

void ANamedObject::setName(const std::string & _name)
{
	m_pName = _name;
}

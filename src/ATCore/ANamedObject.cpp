#include "ANamedObject.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

using namespace std;

ANamedObject::ANamedObject(const std::string & _name)
	:m_pName(_name)
{
}


const char * ANamedObject::name()
{
	return m_pName.c_str();
}

bool ANamedObject::nameIs(const char * _name)
{
	return !strcmp(name(), _name);
}

void ANamedObject::setName(const std::string & _name)
{
	m_pName = _name;
}

#include "ANamedObject.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

using namespace std;

ANamedObject::ANamedObject(const char * _name)
	:m_pName(0)
{
	setName(_name);
}

ANamedObject::~ANamedObject()
{
	free(m_pName);
}

const char * ANamedObject::name()
{
	return m_pName;
}

bool ANamedObject::nameIs(const char * _name)
{
	return !strcmp(m_pName, _name);
}

void ANamedObject::setName(const char * _name)
{
	free(m_pName);
	m_pName = 0;

	size_t str_len = strlen(_name);
	m_pName = (char*)malloc(str_len+1);
	memset(m_pName, 0, str_len + 1);
	memcpy(m_pName, _name, str_len);
}

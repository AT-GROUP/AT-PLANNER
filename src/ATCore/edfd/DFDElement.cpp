
#include "DFDElement.h"
#include "DFDConnection.h"

//======================DFDEntity===============================
DFDEntity::DFDEntity(const std::string & _name, const std::string & comment, const APoint & m_p)
	:DFDElement(_name, comment, m_p)
{
}

DFDElement::Type DFDEntity::type()
{
	return Type::Entity;
}

//======================DFDFunction===============================
DFDFunction::DFDFunction(const std::string & _name, const std::string & comment, const APoint & m_p)
	:DFDElement(_name, comment, m_p)
{
}

DFDElement::Type DFDFunction::type()
{
	return Type::Function;
}

//======================DFDStorage===============================

DFDStorage::DFDStorage(const std::string & _name, const std::string & comment, const APoint & m_p)
	:DFDElement(_name, comment, m_p)
{
}

DFDElement::Type DFDStorage::type()
{
	return Type::Storage;
}

//======================DFDStorage===============================

DFDNFFunction::DFDNFFunction(const std::string & _name, const std::string & comment, const APoint & m_p)
	:DFDElement(_name, comment, m_p)
{
}

DFDElement::Type DFDNFFunction::type()
{
	return Type::NFFunction;
}

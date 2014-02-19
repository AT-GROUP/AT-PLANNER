
#include "DFDElement.h"
#include "DFDConnection.h"
#include <algorithm>

using namespace std;

DFDElement::DFDElement(const std::string & _name, const std::string & comment, const APoint & m_p)
	:ANamedObject(_name), mComment(comment), Mouse_pos(m_p)
{
	mDetalization.used = false;
}

bool DFDElement::isDetalized() const
{
	return mDetalization.used;
}

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

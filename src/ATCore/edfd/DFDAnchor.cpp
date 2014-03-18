#include "DFDConnection.h"
#include "DFDAnchor.h"


DFDAnchor::DFDAnchor(const std::string & _name, const std::string & comment, const APoint & m_p)
	:DFDElement(_name, comment, m_p)
{
}


DFDElement::Type DFDAnchor::type() const
{
	return Type::Anchor;
}

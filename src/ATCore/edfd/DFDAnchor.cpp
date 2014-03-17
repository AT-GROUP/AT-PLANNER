#include "DFDConnection.h"
#include "DFDAnchor.h"


DFDAnchor::DFDAnchor(const std::string & _name, const std::string & comment, const APoint & m_p, const std::vector<std::shared_ptr<DFDConnection>> connList)
	:DFDElement(_name, comment, m_p), connectionList(connList)
{
}


DFDElement::Type DFDAnchor::type() const
{
	return Type::Anchor;
}

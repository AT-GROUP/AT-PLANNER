
#include "DFDConnection.h"

DFDConnection::DFDConnection(const std::string & _name, const std::shared_ptr<DFDElement> src, const std::shared_ptr<DFDElement> dest)
	:ANamedObject(_name), m_pSource(src), m_pDest(dest)
{

}

const std::shared_ptr<DFDElement> & DFDConnection::source() const
{
	return m_pSource;
}

const std::shared_ptr<DFDElement> & DFDConnection::dest() const
{
	return m_pDest;
}

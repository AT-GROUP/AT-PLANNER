
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

bool DFDConnection::connectedTo(const std::shared_ptr<DFDElement> & element) const
{
	return (m_pDest == element) || (m_pSource == element);
}

void DFDConnection::relinkTo(const std::shared_ptr<DFDElement> & from, const std::shared_ptr<DFDElement> & to)
{
	if(m_pDest == from)
		m_pDest = to;
	else if(m_pSource == from)
		m_pSource = to;
}
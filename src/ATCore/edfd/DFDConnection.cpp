
#include "DFDConnection.h"

DFDConnection::DFDConnection(const std::string & _name, const std::shared_ptr<DFDElement> src, const std::shared_ptr<DFDElement> dest, const bool s_t_d, const bool d_t_s)
	:ANamedObject(_name), m_pSource(src), m_pDest(dest), s_t_dest(s_t_d), dest_t_s(d_t_s)
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

std::string DFDConnection::sourceName()
{
	return m_pSource->name();
}

std::string DFDConnection::destName()
{
	return m_pDest->name();
}

std::shared_ptr<DFDElement> DFDConnection::nameSource()
{
	return m_pSource;
}

std::shared_ptr<DFDElement> DFDConnection::nameDest()
{
	return m_pDest;
}
/////////////////////////////////////////////////////////////////////

bool DFDConnection::std()
{
	return s_t_dest;
}

bool DFDConnection::dts()
{
	return dest_t_s;
}

void DFDConnection::setSTD(bool t_f)
{
	s_t_dest = t_f;
}

void DFDConnection::setDTS(bool t_f)
{
	dest_t_s = t_f;
}

void DFDConnection::setSTD_data(const std::string & _data)
{
	s_t_d_data = _data;
}

void DFDConnection::setDTS_data(const std::string & _data)
{
	d_t_s_data = _data;
}

std::string DFDConnection::std_d()
{
	return s_t_d_data;
}

std::string DFDConnection::dts_d()
{
	return d_t_s_data;
}
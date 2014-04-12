
#include "DFDConnection.h"

DFDConnection::DFDConnection(const std::string & _name, const std::shared_ptr<DFDElement> src, const std::shared_ptr<DFDElement> dest)
	:ANamedObject(_name), m_pSource(src), m_pDest(dest)
{
	s_t_d_data.push_back("data1"); 
	d_t_s_data.push_back("data2");
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
	return !s_t_d_data.empty();
}

bool DFDConnection::dts()
{
	return !d_t_s_data.empty();
}

void DFDConnection::addSTD_data(const std::string & _data)
{
	s_t_d_data.push_back(_data);
}

void DFDConnection::addDTS_data(const std::string & _data)
{
	d_t_s_data.push_back(_data);
}

std::vector<std::string> DFDConnection::std_d()
{
	return s_t_d_data;
}

std::vector<std::string> DFDConnection::dts_d()
{
	return d_t_s_data;
}

void DFDConnection::clearSTD()
{
	s_t_d_data.clear();
}
void DFDConnection::clearDTS()
{
	d_t_s_data.clear();
}
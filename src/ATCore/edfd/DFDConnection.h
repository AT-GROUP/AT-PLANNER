
#ifndef ATCore_DFDConnection_h
#define ATCore_DFDConnection_h

#include "../config.h"
#include "../ANamedObject.h"
#include "DFDElement.h"
#include <memory>

class AT_CORE_API DFDConnection : public ANamedObject
{
public:
	DFDConnection(const std::string & _name, std::shared_ptr<DFDElement> src, const std::shared_ptr<DFDElement> dest, const bool s_t_d, const bool d_t_s);

	const std::shared_ptr<DFDElement> & source() const;
	const std::shared_ptr<DFDElement> & dest() const;

	std::string sourceName();
	std::string destName();
	std::shared_ptr<DFDElement> nameSource();
	std::shared_ptr<DFDElement> nameDest();

	/////////////////////////////
	bool std();
	bool dts();
	void setSTD(bool t_f);
	void setDTS(bool t_f);
	void setSTD_data(const std::string & _data);
	void setDTS_data(const std::string & _data);

	std::string std_d();
	std::string dts_d();

	double x_to_y;
	///////////////////////////////

	bool connectedTo(const std::shared_ptr<DFDElement> & element) const;
	void relinkTo(const std::shared_ptr<DFDElement> & from, const std::shared_ptr<DFDElement> & to);
private:
	std::shared_ptr<DFDElement> m_pSource, m_pDest;
	bool s_t_dest, dest_t_s;
	std::string s_t_d_data,d_t_s_data;
};

#endif


#ifndef ATCore_DFDConnection_h
#define ATCore_DFDConnection_h

#include "../config.h"
#include "../ANamedObject.h"
#include "DFDElement.h"
#include <memory>

class AT_CORE_API DFDConnection : public ANamedObject
{
public:
	DFDConnection(const std::string & _name, std::shared_ptr<DFDElement> src, const std::shared_ptr<DFDElement> dest);

	const std::shared_ptr<DFDElement> & source() const;
	const std::shared_ptr<DFDElement> & dest() const;

	std::string sourceName()
	{
		return m_pSource->name();
	}

	std::string destName()
	{
		return m_pDest->name();
	}

	std::shared_ptr<DFDElement> nameSource()
	{
		return m_pSource;
	}

	std::shared_ptr<DFDElement> nameDest()
	{
		return m_pDest;
	}

	bool connectedTo(const std::shared_ptr<DFDElement> & element) const;
	void relinkTo(const std::shared_ptr<DFDElement> & from, const std::shared_ptr<DFDElement> & to);
private:
	std::shared_ptr<DFDElement> m_pSource, m_pDest;
};

#endif

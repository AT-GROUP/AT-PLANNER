
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

	std::string source()
	{
		return m_pSource->name();
	}

	std::string dest()
	{
		return m_pDest->name();
	}
private:
	std::shared_ptr<DFDElement> m_pSource, m_pDest;
};

#endif

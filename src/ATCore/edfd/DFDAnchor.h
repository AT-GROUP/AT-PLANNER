#ifndef ATCore_DFDAnchor_h
#define ATCore_DFDAnchor_h

#include "../config.h"
#include "../ANamedObject.h"
#include "DFDElement.h"
#include <string>
#include <vector>
#include <memory>

class DFDConnection;

class AT_CORE_API DFDAnchor : public DFDElement
{
public:
	DFDAnchor(const std::string & _name, const std::string & comment, const APoint & m_p);
	std::vector<std::shared_ptr<DFDConnection>> connections() const;

	virtual Type type() const;

	void addConnection(const std::shared_ptr<DFDConnection> & conn);
	void deleteConnection(const std::shared_ptr<DFDConnection> & conn);
private:
	std::vector<std::shared_ptr<DFDConnection>> connectionList;
};
#endif


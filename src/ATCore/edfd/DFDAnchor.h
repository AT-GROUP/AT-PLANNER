#ifndef ATCore_DFDAnchor_h
#define ATCore_DFDAnchor_h

#include "../config.h"
#include "../ANamedObject.h"
#include <string>
#include <vector>
#include <memory>

class DFDConnection;

class AT_CORE_API DFDAnchor : public ANamedObject
{
public:
	DFDAnchor(){}
	std::vector<std::shared_ptr<DFDConnection>> connections() const;

	void addConnection(const std::shared_ptr<DFDConnection> & conn);
	void deleteConnection(const std::shared_ptr<DFDConnection> & conn);
private:
	std::vector<std::shared_ptr<DFDConnection>> connectionList;
};
#endif
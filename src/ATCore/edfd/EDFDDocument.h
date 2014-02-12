
#ifndef ATEnvironment_EDFDDocument_h
#define ATEnvironment_EDFDDocument_h

#include "../ADocument.h"
#include "DFDElement.h"
#include "DFDConnection.h"
#include <vector>
#include <memory>

struct _xmlNode;

class AT_CORE_API EDFDDocument : public ADocument
{
public:
	EDFDDocument();
	
	void addElement(const std::shared_ptr<DFDElement> & new_element);
	void addConnection(const std::shared_ptr<DFDConnection> & new_connection);

	virtual void serialize(_xmlNode * document_node) const override;
	virtual AError deserialize(_xmlNode * document_node) override;

private:
	std::vector<std::shared_ptr<DFDElement>> mElements;
	std::vector<std::shared_ptr<DFDConnection>> mConnections;
};

#endif

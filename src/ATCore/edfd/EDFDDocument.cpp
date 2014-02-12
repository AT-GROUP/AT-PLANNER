
#include "EDFDDocument.h"
#include "../utils/helpers.h"
#include <libxml/tree.h>

EDFDDocument::EDFDDocument()
{

}

void EDFDDocument::addElement(const std::shared_ptr<DFDElement> & new_element)
{
	mElements.push_back(new_element);
}

void EDFDDocument::addConnection(const std::shared_ptr<DFDConnection> & new_connection)
{
	mConnections.push_back(new_connection);
}

void EDFDDocument::serialize(_xmlNode * document_node) const
{
	xmlNewChild(document_node, NULL, BAD_CAST "sample_node", BAD_CAST "xxxx");
}

AError EDFDDocument::deserialize(_xmlNode * document_node)
{
	xmlNode * sample_node = child_for_path(document_node, "sample_node");
	return AError();
}
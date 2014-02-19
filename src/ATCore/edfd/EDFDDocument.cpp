
#include "EDFDDocument.h"
#include "../utils/helpers.h"
#include <libxml/tree.h>
#include <algorithm>

using namespace std;

EDFDDocument::EDFDDocument()
{

}

ADocument::Type EDFDDocument::type() const
{
	return ADocument::Type::EDFD;
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
//	xmlNewChild(document_node, NULL, BAD_CAST "sample_node", BAD_CAST "xxxx");
}

AError EDFDDocument::deserialize(_xmlNode * document_node)
{
//	xmlNode * sample_node = child_for_path(document_node, "sample_node");
	return AError();
}

bool EDFDDocument::isDetalized() const
{
	for(auto e : mElements)
	{
		if(e->isDetalized())
			return true;
	}

	return false;
}

void EDFDDocument::buildDetalizationLinks(vector<shared_ptr<EDFDDocument>> & edfd_docs)
{
	for(auto e : mElements)
	{
		if(e->isDetalized())
		{
			//e->buildDetalizationLink(edfd_docs);
			
			auto doc_it = find_if(edfd_docs.begin(), edfd_docs.end(), [=](const shared_ptr<EDFDDocument> & doc){ return doc->fileName() == e->mDetalization.document_name;});
	
			if(doc_it != edfd_docs.end())
				e->mDetalization.document = *doc_it;

			edfd_docs.erase(doc_it);
		}
	}

}

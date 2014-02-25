
#include "AArchitectureDocument.h"
#include "../utils/helpers.h"
#include "AArchElement.h"
#include <libxml/tree.h>
#include <memory>

using namespace std;

AArchitectureDocument::AArchitectureDocument()
	:ADocument()
{

}

ADocument::Type AArchitectureDocument::type() const
{
	return ADocument::Type::ArchitectureMaket;
}

void AArchitectureDocument::serialize(_xmlNode * document_node) const
{

}

AError AArchitectureDocument::deserialize(_xmlNode * document_node)
{
	auto els_node = child_for_path(document_node, "elements");
	if(!els_node)
		return AError(AT_ERROR_INVALID_XML, "Elements node not found");

	xml_for_each_child(els_node, el_node)
	{
		shared_ptr<AArchElement> new_elem(AArchElement::createAndDeserialize(el_node));
		//mElements.push_back(new_elem);
	}

	return AError();
}

const std::vector<std::shared_ptr<AArchElementGroup>> & AArchitectureDocument::groups() const
{
	return mElementGroups;
}

void AArchitectureDocument::addGroup(const std::shared_ptr<AArchElementGroup> & new_group)
{
	mElementGroups.push_back(new_group);
}

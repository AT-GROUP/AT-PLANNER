
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
	xmlNode * groups_node = xmlNewChild(document_node, NULL, BAD_CAST "groups", BAD_CAST "");
	
	for(auto g : mElementGroups)
	{
		xmlNode * group_node = xmlNewChild(groups_node, NULL, BAD_CAST "group", BAD_CAST "");
		g->serialize(group_node);
	}
}

AError AArchitectureDocument::deserialize(_xmlNode * document_node)
{
	auto groups_node = child_for_path(document_node, "groups");
	if(!groups_node)
		return AError(AT_ERROR_INVALID_XML, "Groups node not found");

	xml_for_each_child(groups_node, group_node)
	{
		shared_ptr<AArchElementGroup> new_group(AArchElementGroup::createAndDeserialize(group_node));
		mElementGroups.push_back(new_group);
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

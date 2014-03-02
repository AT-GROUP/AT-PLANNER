
#include "AArchitectureDocument.h"
#include "../utils/helpers.h"
#include "AArchElement.h"
#include "AArchLink.h"
#include <libxml/tree.h>
#include <memory>
#include <algorithm>
#include <map>

using namespace std;

//===============Document=====================
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
	//Groups
	xmlNode * groups_node = xmlNewChild(document_node, NULL, BAD_CAST "groups", BAD_CAST "");
	
	vector<AArchElement*> els;

	for(auto g : mElementGroups)
	{
		xmlNode * group_node = xmlNewChild(groups_node, NULL, BAD_CAST "group", BAD_CAST "");
		g->serialize(group_node, els);
	}

	//Links
	xmlNode * links_node = xmlNewChild(document_node, NULL, BAD_CAST "links", BAD_CAST "");
	for(auto l : mLinks)
	{
		xmlNode * link_node = xmlNewChild(links_node, NULL, BAD_CAST "link", BAD_CAST "");
		l->serialize(link_node, els);
	}
}

AError AArchitectureDocument::deserialize(_xmlNode * document_node)
{
	auto groups_node = child_for_path(document_node, "groups");
	if(!groups_node)
		return AError(AT_ERROR_INVALID_XML, "Groups node not found");

	map<int, AArchElement*> elements;

	xml_for_each_child(groups_node, group_node)
	{
		shared_ptr<AArchElementGroup> new_group(AArchElementGroup::createAndDeserialize(group_node, elements));
		mElementGroups.push_back(new_group);
	}

	//Links
	auto links_node = child_for_path(document_node, "links");
	xml_for_each_child(links_node, link_node)
	{
		shared_ptr<AArchLink> new_link(new AArchLink());
		new_link->deserialize(link_node, elements);
		mLinks.push_back(new_link);
	}

	return AError();
}

const std::vector<std::shared_ptr<AArchElementGroup>> & AArchitectureDocument::groups() const
{
	return mElementGroups;
}
/*
std::shared_ptr<AArchElementGroup> AArchitectureDocument::addGroup(const std::string & new_group_name)
{
	shared_ptr<AArchElementGroup> new_group(new AArchElementGroup(new_group_name));
	addGroup(new_group);
	return new_group;
}*/

void AArchitectureDocument::addGroup(const std::shared_ptr<AArchElementGroup> & new_group)
{
	mElementGroups.push_back(new_group);
}

std::shared_ptr<AArchElementGroup> AArchitectureDocument::group(const std::string & group_name)
{
	auto g_it = std::find_if(mElementGroups.begin(), mElementGroups.end(), [=](const std::shared_ptr<AArchElementGroup> & gr){ return gr->name() == "group_name";});
	if(g_it == mElementGroups.end())
		return nullptr;
	else
		return *g_it;
}

shared_ptr<AArchLink> AArchitectureDocument::link(AArchElement * source, AArchElement * dest, const std::string slot_name)
{
	auto l_it = std::find_if(mLinks.begin(), mLinks.end(), [=](const shared_ptr<AArchLink> & ln){
		return (ln->source() == source) && (ln->destination() == dest) && (ln->slotName() == slot_name);
	});

	if(l_it == mLinks.end())
		return nullptr;
	else
		return *l_it;
}

void AArchitectureDocument::createLink(AArchElement * source, AArchElement * dest, const std::string slot_name)
{
	//Check type
	auto slot = dest->slot(slot_name);
	if(slot.type != source->interfaceDeclaration().name())
		return;

	//Check that there is no such link
	auto old_link = link(source, dest, slot_name);
	if(old_link)
		return;

	//Create link
	shared_ptr<AArchLink> new_link(new AArchLink(source, dest, slot_name));
	mLinks.push_back(new_link);
}

const std::vector<std::shared_ptr<AArchLink>> & AArchitectureDocument::links() const
{
	return mLinks;
}

void AArchitectureDocument::removeElement(AArchElement * element)
{
	//Remove links
	auto l = mLinks.begin();

	while(l != mLinks.end())
	{
		if((l->get()->source() == element) || (l->get()->destination() == element))
			l = mLinks.erase(l);
		else
			++l;
	}

	//Remove element
	for(auto & gr : mElementGroups)
	{
		if(gr->removeElement(element))
			return;
	}
}

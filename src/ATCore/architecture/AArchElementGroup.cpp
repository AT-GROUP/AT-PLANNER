
#include "AArchElementGroup.h"
#include "AArchElement.h"
#include "../edfd/DFDElement.h"
#include "../utils/helpers.h"
#include "../ACommandExecutor.h"
#include <libxml/tree.h>
#include <algorithm>

using namespace std;

AArchElementGroup::AArchElementGroup(const std::shared_ptr<DFDElement> & element)
	:m_pDfdElement(element)
{

}

const std::string & AArchElementGroup::name() const
{
	return m_pDfdElement->name();
}

const std::set<std::shared_ptr<AArchElement>> & AArchElementGroup::children() const
{
	return mChildren;
}

void AArchElementGroup::addChild(const std::shared_ptr<AArchElement> & new_element)
{
	mChildren.insert(new_element);
	return;
}

void AArchElementGroup::serialize(_xmlNode * group_node, std::vector<AArchElement*> & els) const
{
	xmlNewProp(group_node, BAD_CAST "child_count" , BAD_CAST to_string(mChildren.size()).c_str());

	//Position
	xmlNewProp(group_node, BAD_CAST "x" , BAD_CAST to_string(mPos.x()).c_str());
	xmlNewProp(group_node, BAD_CAST "y" , BAD_CAST to_string(mPos.y()).c_str());

	//===========Linked DFD element================
	xmlNode * dfd_element_node = xmlNewChild(group_node, NULL, BAD_CAST "dfd_element", BAD_CAST "");
	m_pDfdElement->serialize(dfd_element_node);

	//====================Arch elements==============
	xmlNode * elements_node = xmlNewChild(group_node, NULL, BAD_CAST "elements", BAD_CAST "");

	for(auto c : mChildren)
	{
		els.push_back(c.get());

		xmlNode * element_node = xmlNewChild(elements_node, NULL, BAD_CAST "element", BAD_CAST "");
		c->serialize(element_node);

		xmlNewProp(element_node, BAD_CAST "id", BAD_CAST to_string(els.size()-1).c_str());
	}
}

void AArchElementGroup::deserialize(_xmlNode * group_node, std::map<int, AArchElement*> & elements)
{
	//Position
	const char *_x = xml_prop(group_node, "x"), *_y = xml_prop(group_node, "y");
	mPos.setX(atoi(_x));
	mPos.setY(atoi(_y));

	//Children
	xmlNode * children_node = child_for_path(group_node, "elements");

	xml_for_each_child(children_node, child_node)
	{
		shared_ptr<AArchElement> new_el(AArchElement::createAndDeserialize(child_node, command_executor()));
		addChild(new_el);

		int element_id = atoi(xml_prop(child_node, "id"));
		elements.insert(pair<int, AArchElement*>(element_id, new_el.get()));
	}
}

AArchElementGroup * AArchElementGroup::createAndDeserialize(_xmlNode * group_node, std::map<int, AArchElement*> & elements)
{
	//DFD element
	xmlNode * dfd_element_node = child_for_path(group_node, "dfd_element");
	shared_ptr<DFDElement> dfd_element(DFDElement::createAndDeserialize(dfd_element_node));

	AArchElementGroup * new_group = new AArchElementGroup(dfd_element);
	new_group->deserialize(group_node, elements);

	return new_group;

}

const DFDElement * AArchElementGroup::dfdElement() const
{
	return m_pDfdElement.get();
}

const APoint & AArchElementGroup::pos() const
{
	return mPos;
}

void AArchElementGroup::setPos(const APoint & new_pos)
{
	mPos = new_pos;
}

bool AArchElementGroup::removeElement(AArchElement * element)
{
	auto it = std::find_if(mChildren.begin(), mChildren.end(), [=](const std::shared_ptr<AArchElement> & el){return el.get() == element;});
	if(it == mChildren.end())
		return false;
	else
	{
		mChildren.erase(it);
		return true;
	}
}

std::shared_ptr<AArchElement> AArchElementGroup::findElementWithInterface(const std::string & interface_name) const
{
	auto it = std::find_if(mChildren.begin(), mChildren.end(), [=](const std::shared_ptr<AArchElement> & el){return el->interfaceDeclaration().name() == interface_name;});
	if(it == mChildren.end())
		return nullptr;
	else
	{
		return *it;
	}
}

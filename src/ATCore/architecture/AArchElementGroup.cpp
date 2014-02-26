
#include "AArchElementGroup.h"
#include "AArchElement.h"
#include "../edfd/DFDElement.h"
#include "../utils/helpers.h"
#include <libxml/tree.h>

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

void AArchElementGroup::serialize(_xmlNode * group_node) const
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
		xmlNode * element_node = xmlNewChild(elements_node, NULL, BAD_CAST "element", BAD_CAST "");
		c->serialize(element_node);
	}
}

void AArchElementGroup::deserialize(_xmlNode * group_node)
{
	//Position
	const char *_x = xml_prop(group_node, "x"), *_y = xml_prop(group_node, "y");
	mPos.setX(atoi(_x));
	mPos.setY(atoi(_y));

	//Children
	xmlNode * children_node = child_for_path(group_node, "elements");

	xml_for_each_child(children_node, child_node)
	{
		shared_ptr<AArchElement> new_el(AArchElement::createAndDeserialize(child_node));
		addChild(new_el);
	}
}

AArchElementGroup * AArchElementGroup::createAndDeserialize(_xmlNode * group_node)
{
	//DFD element
	xmlNode * dfd_element_node = child_for_path(group_node, "dfd_element");
	shared_ptr<DFDElement> dfd_element(DFDElement::createAndDeserialize(dfd_element_node));

	AArchElementGroup * new_group = new AArchElementGroup(dfd_element);
	new_group->deserialize(group_node);

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

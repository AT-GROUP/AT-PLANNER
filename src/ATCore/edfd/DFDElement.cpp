
#include "DFDElement.h"
#include "DFDConnection.h"
#include "../utils/helpers.h"
#include <algorithm>
#include <libxml/tree.h>

using namespace std;

inline const char * const BoolToString(bool b)
{
  return b ? "true" : "false";
}

DFDElement::DFDElement(const std::string & _name, const std::string & comment, const APoint & m_p)
	:ANamedObject(_name), mComment(comment), Mouse_pos(m_p)
{
	mDetalization.used = false;
}

bool DFDElement::isDetalized() const
{
	return mDetalization.used;
}

void DFDElement::serialize(_xmlNode * element_node) const
{
	xmlNewProp (element_node, BAD_CAST "name" , BAD_CAST name().c_str());
	xmlNewProp (element_node, BAD_CAST "xPos" , BAD_CAST to_string(Mouse_pos.x()).c_str());
	xmlNewProp (element_node, BAD_CAST "yPos" , BAD_CAST to_string(Mouse_pos.y()).c_str());
	xmlNewProp(element_node, BAD_CAST "type" , BAD_CAST to_string(static_cast<int>(type())).c_str());
	xmlNewProp(element_node, BAD_CAST "detal" , BAD_CAST BoolToString(mDetalization.used));

	xmlNewProp (element_node, BAD_CAST "id" , BAD_CAST to_string(id()).c_str());

	if (mDetalization.used)
	{
		xmlNewProp(element_node, BAD_CAST "detal_doc_name" , BAD_CAST mDetalization.document_name.c_str());
		//xmlNewProp(child_node, BAD_CAST "type" , BAD_CAST e->mDetalization.document);
	}
}

AError DFDElement::deserialize(_xmlNode * element_node)
{
	//Name
	ANamedObject::deserialize(element_node);

	//Position
	const char *_xPos = xml_prop(element_node, "xPos");
	const char *_yPos = xml_prop(element_node, "yPos");
	Mouse_pos.setX(atoi(_xPos));
	Mouse_pos.setY(atoi(_yPos));

	const char * cid = xml_prop(element_node, "id");
	setId(atoi(cid));

	return AError();
}

bool DFDElement::isSameAs(DFDElement * another) const
{
	bool res = true;
	res = res && (type() == another->type());
	res = res && (name() == another->name());
	return res;
}

int DFDElement::id() const
{
	return mId;
}

void DFDElement::setId(const int new_id)
{
	mId = new_id;
}

DFDElement * DFDElement::createAndDeserialize(_xmlNode * element_node)
{
	auto _type = atoi(xml_prop(element_node, "type"));

	DFDElement * new_el(nullptr);

	switch(static_cast<DFDElement::Type>(_type))
	{
	case DFDElement::Type::Entity:
		{
			new_el = new DFDEntity();
			break;
		}
	case DFDElement::Type::Function:
		{
			new_el = new DFDFunction();
			break;
		}
	case DFDElement::Type::Storage:
		{
			new_el = new DFDStorage();
			break;
		}
	case DFDElement::Type::NFFunction:
		{
			new_el = new DFDNFFunction();
			break;
		}
	default:
		break;
	}

	new_el->deserialize(element_node);

	return new_el;
}

//======================DFDEntity===============================
DFDEntity::DFDEntity(const std::string & _name, const std::string & comment, const APoint & m_p)
	:DFDElement(_name, comment, m_p)
{
}

DFDElement::Type DFDEntity::type() const
{
	return Type::Entity;
}

//======================DFDFunction===============================
DFDFunction::DFDFunction(const std::string & _name, const std::string & comment, const APoint & m_p)
	:DFDElement(_name, comment, m_p)
{
}

DFDElement::Type DFDFunction::type() const
{
	return Type::Function;
}

//======================DFDStorage===============================

DFDStorage::DFDStorage(const std::string & _name, const std::string & comment, const APoint & m_p)
	:DFDElement(_name, comment, m_p)
{
}

DFDElement::Type DFDStorage::type() const
{
	return Type::Storage;
}

//======================DFDStorage===============================

DFDNFFunction::DFDNFFunction(const std::string & _name, const std::string & comment, const APoint & m_p)
	:DFDElement(_name, comment, m_p)
{
}

DFDElement::Type DFDNFFunction::type() const
{
	return Type::NFFunction;
}

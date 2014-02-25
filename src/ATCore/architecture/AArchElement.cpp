
#include "AArchElement.h"
#include <libxml/tree.h>
#include "../utils/helpers.h"
#include <string>

using namespace std;

AArchElement::AArchElement(const std::string & _name)
{

}

AArchElement * AArchElement::createAndDeserialize(_xmlNode * element_node)
{
	AArchElement * result = nullptr;

	//Get type
	auto type = static_cast<Type>(atoi(xml_prop(element_node, "type")));
	
	if(type == AArchElement::Type::Functional)
	{
		/*
		For functional component we will find it's library
		and get programm interface from it.
		*/
		result = new AArchFuncElement();
	}
	else
	{
		/*
		For informational component we will find linked document.
		*/
		result = new AArchInfoElement();
	}

	result->deserialize(element_node);

	return result;
}

void AArchElement::serialize(_xmlNode * element_node) const
{
	
}

AError AArchElement::deserialize(_xmlNode * element_node)
{
	auto cname = xml_prop(element_node, "name");
	setName(string(cname));

	//Position
	mPos.setX(atof(xml_prop(element_node, "x")));
	mPos.setY(atof(xml_prop(element_node, "y")));

	return AError();
}

const APoint & AArchElement::pos() const
{
	return mPos;
}

void AArchElement::setPos(const APoint & new_pos)
{
	mPos = new_pos;
}

//=====================Functional element==========================

AArchFuncElement::AArchFuncElement(const std::string & _name)
	:AArchElement(_name)
{
	mInterface.inputs.push_back(APIKInterface::Slot("Solver"));
	mInterface.inputs.push_back(APIKInterface::Slot("Scenario"));
	
	mConfig.params.push_back(APIKConfig::Property("type"));
}

AArchElement::Type AArchFuncElement::type() const
{
	return AArchElement::Type::Functional;
}

bool AArchFuncElement::hasConfig() const
{
	return !mConfig.params.empty();
}

const APIKInterface & AArchFuncElement::interfaceDeclaration() const
{
	return mInterface;
}

//=====================Informational element==========================

AArchInfoElement::AArchInfoElement(const std::string & _name)
	:AArchElement(_name)
{

}

AArchElement::Type AArchInfoElement::type() const
{
	return AArchElement::Type::Informational;
}

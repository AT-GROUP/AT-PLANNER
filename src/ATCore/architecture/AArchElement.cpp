
#include "AArchElement.h"
#include <libxml/tree.h>
#include "../utils/helpers.h"
#include "AArchElementFactory.h"
#include <string>
#include <algorithm>

using namespace std;

AArchElement::AArchElement(APIKInterface & _intf, const std::string & _name)
	:ANamedObject(_name), mInterface(_intf)
{

}

AArchElement * AArchElement::createAndDeserialize(_xmlNode * element_node, AArchElementFactory * arch_factory)
{
	AArchElement * result = nullptr;

	//Get type
	auto type = static_cast<Type>(atoi(xml_prop(element_node, "type")));
	
	xmlNode * intf_node = child_for_path(element_node, "interface");
	auto c_interface_name = xml_prop(intf_node, "name");

	/*if(type == AArchElement::Type::Functional)
	{
		
		For functional component we will find it's library
		and get programm interface from it. For informational component we will find linked document.
		
		

		
	}
	else
	{
		result = new AArchInfoElement();
	}*/

	result = arch_factory->createArchPIKInstance(type, string(c_interface_name));

	result->deserialize(element_node);

	return result;
}

void AArchElement::serialize(_xmlNode * element_node) const
{
	xmlNewProp (element_node, BAD_CAST "name" , BAD_CAST name().c_str());
	xmlNewProp (element_node, BAD_CAST "x" , BAD_CAST to_string(mPos.x()).c_str());
	xmlNewProp (element_node, BAD_CAST "y" , BAD_CAST to_string(mPos.y()).c_str());

	xmlNewProp(element_node, BAD_CAST "type" , BAD_CAST to_string(static_cast<int>(type())).c_str());

	//Interface
	xmlNodePtr intf_node = xmlNewChild(element_node, NULL, BAD_CAST "interface", BAD_CAST "");
	xmlNewProp(intf_node, BAD_CAST "name" , BAD_CAST mInterface.name().c_str());
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

void AArchElement::setPos(const float x, const float y)
{
	mPos.setX(x);
	mPos.setY(y);
}

APIKInterface::Slot & AArchElement::slot(const std::string & slot_name)
{
	auto & it = std::find_if(mInterface.inputs.begin(), mInterface.inputs.end(), [=](const APIKInterface::Slot & slot){return slot.name == slot_name;});
	return *it;
}

const APIKInterface & AArchElement::interfaceDeclaration() const
{
	return mInterface;
}

//=====================Functional element==========================

AArchFuncElement::AArchFuncElement(APIKInterfaceFunc & intf, const std::string & _name)
	:AArchElement(intf, _name), mConfig(APIKConfigInstance(intf.configInterface))
{
//	mInterface.inputs.push_back(APIKInterface::Slot("Solver"));
//	mInterface.inputs.push_back(APIKInterface::Slot("Scenario"));
	
//	mConfig.params.push_back(APIKConfig::Property("type"));
}

const APIKInterfaceFunc & AArchFuncElement::archInterface() const
{
	return static_cast<const APIKInterfaceFunc&>(mInterface);
}

APIKInterfaceFunc & AArchFuncElement::archInterface()
{
	return static_cast<APIKInterfaceFunc&>(mInterface);
}

AArchElement::Type AArchFuncElement::type() const
{
	return AArchElement::Type::Functional;
}

bool AArchFuncElement::hasConfig() const
{
	//return !mConfig.params.empty();
	return mConfig.exists();
}

const APIKConfigInstance & AArchFuncElement::config() const
{
	return mConfig;
}

APIKConfigInstance & AArchFuncElement::config()
{
	return mConfig;
}

bool AArchFuncElement::mustBeDeveloped() const
{
	if(hasConfig())
		return true;
	else
	{
		if(interfaceDeclaration().name() == "SimpleOperation")
			return true;
		else
			return false;
	}
}
//=====================Informational element==========================

AArchInfoElement::AArchInfoElement(APIKInterfaceInf & intf, const std::string & _name)
	:AArchElement(intf, _name)
{

}

AArchElement::Type AArchInfoElement::type() const
{
	return AArchElement::Type::Informational;
}

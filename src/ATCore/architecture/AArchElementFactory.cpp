
#include "AArchElementFactory.h"
#include "AArchElement.h"
#include "../utils/helpers.h"
#include <libxml/tree.h>
#include <algorithm>

using namespace std;

AArchElementFactory::AArchElementFactory()
{
	loadPIKDefinitions();
}

AError AArchElementFactory::loadPIKDefinitions()
{
	//Find xml document
	xmlDoc * doc = xmlReadFile("kb/pikdb.xml", 0, 0);
	
	if(!doc)
		return AError(AT_ERROR_INVALID_FILE);

	//Get root node
	xmlNode * root_element = xmlDocGetRootElement(doc);
	
	if(!root_element)
	{
		xmlFreeDoc(doc);
		xmlCleanupParser();
		return AError(AT_ERROR_INVALID_XML);
	}

	//Deserialize PIKs classes
	auto res = deserialize(root_element);


	//Close doc and clean parser
	xmlFreeDoc(doc);
	xmlCleanupParser();

	return res;
}

AError AArchElementFactory::deserialize(_xmlNode * doc_node)
{
	xml_for_each_child(doc_node, interface_node)
	{
		int ntype = atoi(xml_prop(interface_node, "type"));

		switch(static_cast<APIKInterface::Type>(ntype))
		{
		case APIKInterface::Type::Func:
			{
				APIKInterfaceFunc func;
				func.deserialize(interface_node);
				mFuncInteraces.push_back(func);
				break;
			}
		case APIKInterface::Type::Info:
			{
				APIKInterfaceInf inf;
				inf.deserialize(interface_node);
				mInfoInteraces.push_back(inf);
				break;
			}
		};
	}

	return AError();
}

const std::vector<APIKInterfaceInf> & AArchElementFactory::infPIKs() const
{
	return mInfoInteraces;
}

const std::vector<APIKInterfaceFunc> & AArchElementFactory::funcPIKs() const
{
	return mFuncInteraces;
}

AArchElement * AArchElementFactory::createArchPIKInstance(AArchElement::Type type, const std::string & interface_name)
{
	AArchElement * new_el(nullptr);

	//Find interface
	if(type == AArchElement::Type::Functional)
	{
		auto it = find_if(mFuncInteraces.begin(), mFuncInteraces.end(), [=](const APIKInterfaceFunc & intf){return intf.name() == interface_name;});
		new_el = new AArchFuncElement(*it, interface_name + " instance");
	}
	else if(type == AArchElement::Type::Informational)
	{
		auto it = find_if(mInfoInteraces.begin(), mInfoInteraces.end(), [=](const APIKInterfaceInf & intf){return intf.name() == interface_name;});
		new_el = new AArchInfoElement(*it, interface_name + " instance");
	}
	return new_el;
}

AArchElement * AArchElementFactory::createArchPIKInstance(const std::string & interface_name)
{
	AArchElement::Type type = AArchElement::Type::Functional;
	auto it = find_if(mFuncInteraces.begin(), mFuncInteraces.end(), [=](const APIKInterfaceFunc & intf){return intf.name() == interface_name;});
	if(it == mFuncInteraces.end())
		type = AArchElement::Type::Informational;

	return createArchPIKInstance(type, interface_name);
}
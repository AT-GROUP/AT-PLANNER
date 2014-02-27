
#include "AArchElementFactory.h"
#include "../utils/helpers.h"
#include <libxml/tree.h>

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

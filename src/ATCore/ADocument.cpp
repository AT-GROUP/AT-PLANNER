
#include "ADocument.h"

#include <libxml/tree.h>
#include <libxml/parser.h>

AError ADocument::saveToFile(const std::string & file_name)
{
	xmlDocPtr doc = xmlNewDoc(BAD_CAST XML_DEFAULT_VERSION);
	xmlNodePtr root_node = xmlNewNode(NULL, BAD_CAST "document");

    xmlNodeSetContent(root_node, BAD_CAST "");
	xmlDocSetRootElement(doc, root_node);

	serialize(root_node);

	xmlSetDocCompressMode(doc, 0);
	xmlSaveFormatFile(file_name.c_str(), doc, 1);
	xmlFreeDoc(doc);

	return AError();
}

AError ADocument::loadFromFile(const std::string & file_name)
{
	xmlDoc * doc = xmlReadFile(file_name.c_str(), 0, 0);
	
	if(!doc)
		return AError(AT_ERROR_INVALID_FILE);

	xmlNode * root_element = xmlDocGetRootElement(doc);
	
	if(!root_element)
	{
		xmlFreeDoc(doc);
		xmlCleanupParser();
		return AError(AT_ERROR_INVALID_XML);
	}

	auto res = deserialize(root_element);

	xmlFreeDoc(doc);
	xmlCleanupParser();

	return res;
}


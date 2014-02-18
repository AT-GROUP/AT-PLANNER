
#ifndef ATCore_helpers_h
#define ATCore_helpers_h

#include "../config.h"
#include <string>

struct _xmlNode;

//LIBXML

AT_CORE_API _xmlNode * child_for_path(_xmlNode * root_node, const std::string & path);

#define xml_for_each_child(root, iterator) for(xmlNode * iterator = root->children; iterator; iterator = iterator->next) if (iterator->type == XML_ELEMENT_NODE)


#endif

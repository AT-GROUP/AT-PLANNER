
#ifndef ATCore_helpers_h
#define ATCore_helpers_h

#include "../config.h"
#include <string>

struct _xmlNode;

AT_CORE_API void split_file_path(const std::string & path, std::string & dir, std::string & fname);

//LIBXML

AT_CORE_API _xmlNode * child_for_path(_xmlNode * root_node, const std::string & path);



#define xml_for_each_child(root, iterator) for(xmlNode * iterator = root->children; iterator; iterator = iterator->next) if (iterator->type == XML_ELEMENT_NODE)
#define xml_prop(node, prop_name) (const char*)xmlGetProp(node, (xmlChar*)prop_name)

#endif

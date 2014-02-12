
#ifndef ATCore_helpers_h
#define ATCore_helpers_h

#include "../config.h"
#include <string>

struct _xmlNode;

AT_CORE_API _xmlNode * child_for_path(_xmlNode * root_node, const std::string & path);


#endif

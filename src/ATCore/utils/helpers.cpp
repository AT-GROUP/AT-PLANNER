
#include "helpers.h"
#include <libxml/tree.h>

using namespace std;

_xmlNode * child_for_path(_xmlNode * root_node, const std::string & path)
{
	if(path.empty())
		return nullptr;

	string s_path(path);
    size_t slash_pos = s_path.find("/");
    
	string topNodeName;
	bool isBottomNode = true;
    if(slash_pos != string::npos) //If found slash
    {
		isBottomNode = false;
		topNodeName = s_path.substr(0, slash_pos);
	}
	else
		topNodeName = s_path;

	for (xmlNode * cur_node = root_node->children; cur_node; cur_node = cur_node->next)
	{
		if (cur_node->type == XML_ELEMENT_NODE)
		{
			if(!strcmp((const char*)cur_node->name, topNodeName.c_str()))
			{
				if(isBottomNode)
					return cur_node;
				else
				{
					return child_for_path(cur_node, s_path.substr(slash_pos+1).c_str());
				}
			}
		}
	}

	return 0;
}

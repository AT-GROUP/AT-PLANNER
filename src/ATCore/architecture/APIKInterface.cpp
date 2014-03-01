
#include "APIKInterface.h"
#include "../AError.h"
#include <libxml/tree.h>
#include "../utils/helpers.h"

using namespace std;

//========================Base==============================
AError APIKInterface::deserialize(_xmlNode * pik_node)
{
	//Name
	ANamedObject::deserialize(pik_node);

	//Description
	auto cdescr = xml_prop(pik_node, "descr");
	description = string(cdescr);

	//Input
	xmlNode * inputs_node = child_for_path(pik_node, "input");
	if(inputs_node)
	{
		xml_for_each_child(inputs_node, input_node)
		{
			auto cname = xml_prop(input_node, "name");
			auto ctype = xml_prop(input_node, "type");

			inputs.push_back(Slot(cname, ctype));
		}
	}

	return AError();
}


//========================Functional=========================
AError APIKInterfaceInf::deserialize(_xmlNode * pik_node)
{
	AError res = APIKInterface::deserialize(pik_node);

	return res;
}


//========================Informational=========================
AError APIKInterfaceFunc::deserialize(_xmlNode * pik_node)
{
	AError res = APIKInterface::deserialize(pik_node);

	xmlNode * config_node = child_for_path(pik_node, "config");
	if(config_node)
	{
		xml_for_each_child(config_node, param_node)
		{
			auto cparam_name = xml_prop(param_node, "name");
			APIKConfig::Property new_prop(cparam_name);

			configInterface.params.push_back(new_prop);
		}
	}

	return res;
}

#include "AProjectNode.h"
#include "../AFile.h"
#include "../utils/helpers.h"

AProjectNode::AProjectNode(const std::string & _name)
	:ANamedObject(_name)
{

}

void AProjectNode::addChild(AProjectNode * child)
{
	mChildren.push_back(child);
}

void AProjectNode::removeChild(AProjectNode * child)
{
	auto i = std::find(mChildren.begin(), mChildren.end(), child);
	if(i != mChildren.end())
	{
		mChildren.erase(i);
	}
}

std::vector<AProjectNode*> & AProjectNode::getChild()
{
	return mChildren;
}

AProjectNode* AProjectNode::getChild(int _i)
{
	try {
		return mChildren.at(_i);
	}
	catch (std::out_of_range &) {
		return NULL;

	};

}

void AProjectNode::serialize(xmlNode * xml_node) const
{
	xmlNodeSetContent(xml_node, BAD_CAST "");

	for(auto c : mChildren)
	{
		
		xmlNodePtr child_node = xmlNewNode(NULL, BAD_CAST c->name());
		xmlAddChild(xml_node, child_node);

		
		if (c->type() == AProjectNode::Type::File)
			xmlNewProp (child_node, BAD_CAST "type" , BAD_CAST "file");
		else
		{
			xmlNewProp (child_node, BAD_CAST "type" , BAD_CAST "group");
		};
		
		c->serialize(child_node);
	}
}


void AProjectNode::deserialize(xmlNodePtr xml_ptr)
{
	xml_for_each_child(xml_ptr, child)
	{
		struct _xmlAttr * _prop = xml_ptr->properties;
		const xmlChar * _prop_type = xmlGetProp(xml_ptr, _prop->name);
		const char * _node_type = (const char*) _prop_type;
		/*if (strcmp(_node_type,"file")==0) 
		{
			AFile * new_file = new AFile((const char*) xml_ptr->name);
			AFileProjectNode * new_node = new AFileProjectNode(new_file);
			addChild(new_node);
			new_node->deserialize(xml_ptr);			
		}
		else 
		{
			AGroupProjectNode * new_node = new AGroupProjectNode((const char*) xml_ptr->name);
			addChild(new_node);
			new_node->deserialize(xml_ptr);
		}*/
		AProjectNode * new_node = createAndDeserialize(child);
		addChild(new_node);
	}
}


AProjectNode * AProjectNode::createAndDeserialize(xmlNode * xml_node)
{
	const char * _node_type = (const char*) xmlGetProp(xml_node, (xmlChar*)"type");
	AProjectNode * new_node = nullptr;
	if(!strcmp(_node_type, "file"))
	{
		new_node = new AFileProjectNode(0);
	}
	else if(!strcmp(_node_type, "group"))
	{
		new_node = new AGroupProjectNode(0);
	}

	new_node->deserialize(xml_node);

	return new_node;
}


/*void AProjectNode::deserialize(xmlNodePtr xml_ptr)
{
	xml_ptr = xml_ptr->xmlChildrenNode;
	//int _i = 0;
	while (xml_ptr != NULL)
	{	

// #define xml_for_each_child (root, iterator) for(xmlNode * iterator = root->children; iterator; iterator = iterator->next) if (iterator->type == XML_ELEMENT_NODE)
		if (xml_ptr->type == XML_ELEMENT_NODE)
		{
			struct _xmlAttr * _prop = xml_ptr->properties;
			const xmlChar * _prop_type = xmlGetProp(xml_ptr, _prop->name);
			const char * _node_type = (const char*) _prop_type;
			if (strcmp(_node_type,"file")==0) 
			{
				AFile * new_file = new AFile((const char*) xml_ptr->name);
				AFileProjectNode * new_node = new AFileProjectNode(new_file);
				addChild(new_node);
				new_node->deserialize(xml_ptr);			
			}
			else 
			{
				AGroupProjectNode * new_node = new AGroupProjectNode((const char*) xml_ptr->name);
				addChild(new_node);
				new_node->deserialize(xml_ptr);
			}

		}
		xml_ptr = xml_ptr->next;
		//++_i;
	}
}*/

/*
xmlNode * AProjectNode::serialize(xmlNode * parent_node, USBuilding * building)
{
	xmlNode * project_node = xmlNewChild(parent_node, NULL, BAD_CAST "project_node", BAD_CAST "");
	
	xmlNewProp(project_node, BAD_CAST "name", BAD_CAST name().c_str());

	char buffer[128];
	sprintf(buffer, "%d", type());

	xmlNewProp(project_node, BAD_CAST "type", BAD_CAST buffer);

	for(auto c : mChildren)
	{
		c->serialize(project_node, building);
	}

	return project_node;
}

void AProjectNode::deserialize(xmlNode * node, USBuilding * building)
{
	const char * file_name = xml_node_attr_data(node, "name");
	setName(file_name);

	xml_for_each_child(node, child_node)
	{
		AProjectNode * new_node = 0;

		int child_type = atoi(xml_node_attr_data(child_node, "type"));
		
		if(child_type == AProjectNode::Group)
			new_node = new AGroupProjectNode("new_group");
		else if(child_type == AProjectNode::File)
			new_node = new AFileProjectNodede();
		else if(child_type == AProjectNode::BuildingElement)
			new_node = new USElementProjectNode();

		if(new_node)
			new_node->deserialize(child_node, building);

		mChildren.push_back(new_node);
	}
}
*/
//================AGroupProjectNode=====================
AGroupProjectNode::AGroupProjectNode(const std::string & _name)
	:AProjectNode(_name)
{

}

AProjectNode::Type AGroupProjectNode::type()
{

	return AProjectNode::Type::Group;
}


//==============ARootProjectNode=================
ARootProjectNode::ARootProjectNode(const std::string & project_name)
	:AGroupProjectNode(project_name)
{

}

AProjectNode::Type ARootProjectNode::type()
{
	return AProjectNode::Type::ProjectRoot;
}

//==============AFileProjectNodede=================
AFileProjectNode::AFileProjectNode(AFile * _file)
	:AGroupProjectNode("unnamed"), m_pFile(0)
{
	if(_file)
	{
		setName(_file->name());
		m_pFile = _file;
	}

}

AProjectNode::Type AFileProjectNode::type()
{
	return AProjectNode::Type::File;
}
/*
xmlNode * AFileProjectNodede::serialize(xmlNode * parent_node, USBuilding * building)
{
	xmlNode * node = AProjectNode::serialize(parent_node, building);

	char buffer[128];
	sprintf(buffer, "%d", std::distance(building->fileContainer()->mFiles.begin(), std::find(building->fileContainer()->mFiles.begin(), building->fileContainer()->mFiles.end(), m_pFile)));
	xmlNewProp(node, BAD_CAST "file_index", BAD_CAST buffer);

	return node;
}

void AFileProjectNodede::deserialize(xmlNode * node, USBuilding * building)
{
	AProjectNode::deserialize(node, building);

	int file_index = atoi(xml_node_attr_data(node, "file_index"));

	USFile * file = building->fileContainer()->mFiles[file_index];
	m_pFile = file;
	setName(file->name().c_str());
}
*/
AFile * AFileProjectNode::file()
{
	return m_pFile;
}

void AFileProjectNode::serialize(xmlNode* xml_node)
{
	
}

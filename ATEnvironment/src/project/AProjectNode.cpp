#include "AProjectNode.h"
#include "../core/AFile.h"

AProjectNode::AProjectNode(const char * _name)
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
AGroupProjectNode::AGroupProjectNode(const char * _name)
	:AProjectNode(_name)
{

}

int AGroupProjectNode::type()
{
	return AProjectNode::Group;
}


//==============ARootProjectNode=================
ARootProjectNode::ARootProjectNode(const char * project_name)
	:AGroupProjectNode(project_name)
{

}

int ARootProjectNode::type()
{
	return AProjectNode::ProjectRoot;
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

int AFileProjectNode::type()
{
	return AProjectNode::File;
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

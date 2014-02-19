#include "AProject.h"
#include "AProjectNode.h"
#include "../utils/helpers.h"
//#include "dll/libxml2"

using namespace std;


//Writing and binding nodes with parent node and saving into output file
/*void writeNode (std::vector<AProjectNode*> _vector, xmlNodePtr _parent)
{
	while (_vector.empty() == false)
	{
		
		xmlNodePtr _child_node = xmlNewNode(NULL, BAD_CAST _vector.at(0)->name());
		xmlAddChild(_parent, _child_node);
		xmlNodeSetContent(_child_node, BAD_CAST "");

		writeNode(_vector.at(0)->getChild(), _child_node);

		_vector.erase(_vector.begin());
		
	}
}*/

AProject::AProject(const std::string & project_name, const std::string & project_dir)
	:ANamedObject(project_name), m_pRootNode(0), mProjectFileName(project_name + ".atprj"), mProjectDir(project_dir)
{
	m_pRootNode = new ARootProjectNode(project_name);
}

ARootProjectNode * AProject::rootNode()
{
	return m_pRootNode;
}

std::string AProject::projectDir() const
{
	return mProjectDir;
}

void AProject::setProjectDir(const std::string & dir)
{
	mProjectDir = dir;
}

const std::string & AProject::fileName() const
{
	return mProjectFileName;
}

void AProject::setFileName(std::string & f_name)
{
	mProjectFileName = f_name;
}

void AProject::serialize(xmlNodePtr root_node) const
{
	//Project name
	xmlNewProp(root_node, BAD_CAST "name" , BAD_CAST name().c_str());

	//Serialize project tree and save all changed referenced files
	xmlNode * project_tree_node = xmlNewChild(root_node, NULL, BAD_CAST "project_root_node", BAD_CAST "");
	m_pRootNode->serialize(project_tree_node);
}

AError AProject::deserialize(xmlNodePtr root_node)
{
	auto cproject_name = xml_prop(root_node, "name");
	setName(string(cproject_name));

	xmlNode * project_tree_node = child_for_path(root_node, "project_root_node");
	m_pRootNode->deserialize(project_tree_node);

	return AError();
}

bool AProject::hasUnsavedChanges() const
{
	return true;
}

#include "AProject.h"
#include "AProjectNode.h"
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

void AProject::serialize(xmlNodePtr root_node) const
{
	//Serialize project tree
	m_pRootNode->serialize(root_node);

	//Save all changed referenced files
}

void AProject::deserialize(xmlNodePtr root_node)
{
	m_pRootNode->deserialize(root_node);
}

bool AProject::hasUnsavedChanges() const
{
	return true;
}

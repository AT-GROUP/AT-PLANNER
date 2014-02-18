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

AProject::AProject(const char * project_name, const char * project_dir)
	:ANamedObject(project_name), m_pRootNode(0), mProjectFileName(string(project_name) + ".atprj"), mProjectDir(project_dir)
{
	m_pRootNode = new ARootProjectNode(project_name);
}

ARootProjectNode * AProject::rootNode()
{
	return m_pRootNode;
}

void AProject::save()
{
	//Create XML-structure of project file
	xmlDocPtr doc = xmlNewDoc(BAD_CAST XML_DEFAULT_VERSION);
    xmlNodePtr root_node = xmlNewNode(NULL, BAD_CAST "at_project");
	xmlNodeSetContent(root_node, BAD_CAST "");
	xmlDocSetRootElement(doc, root_node);

	//Write it
	xmlSetDocCompressMode(doc, 9);

	string project_file_path = mProjectDir + "/" + mProjectFileName;
	xmlSaveFormatFile(project_file_path.c_str(), doc, 1);
    xmlFreeDoc(doc);

	
	//Save all changed referenced files
	
}

void AProject::saveChanges()
{
	try {
	std::vector<AProjectNode*> _child_vector;
	AProjectNode * _child;
	//Save all changed referenced files
	xmlDocPtr doc = xmlNewDoc(BAD_CAST XML_DEFAULT_VERSION);
	xmlNodePtr root_node = xmlNewNode(NULL, BAD_CAST  mProjectFileName.c_str());
	xmlNodeSetContent(root_node, BAD_CAST "");
	
	//Finding vector with project_structure
	/*_child_vector = m_pRootNode->getChild();

	writeNode(_child_vector,root_node);*/

	m_pRootNode->serialize(root_node);

	xmlDocSetRootElement(doc, root_node);
	

	string project_file_path = mProjectDir + "/" + mProjectFileName;
	xmlSaveFormatFile(project_file_path.c_str(), doc, 1);
    xmlFreeDoc(doc);
	}
	catch (std::exception& ex) {

	}
}

std::string AProject::projectDir()
{
	return mProjectDir;
}

void AProject::openProject(xmlNodePtr cur)
{
	m_pRootNode->deserialize(cur);
}


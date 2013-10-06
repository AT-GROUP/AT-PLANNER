#include "AProject.h"
#include "AProjectNode.h"

using namespace std;

AProject::AProject(const char * project_name, const char * project_dir)
	:ANamedObject(project_name), m_pRootNode(0), mProjectFileName(string(project_name) + ".atprj"), mProjectDir(project_dir)
{
	m_pRootNode = new ARootProjectNode("project_name");
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

std::string AProject::projectDir()
{
	return mProjectDir;
}

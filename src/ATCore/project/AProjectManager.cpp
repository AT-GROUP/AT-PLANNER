
#include "AProjectManager.h"
#include "AProject.h"
#include "../utils/helpers.h"

using namespace std;

AProjectManager::AProjectManager()
	:m_pProject(nullptr)
{

}

AProject * AProjectManager::project() const
{
	return m_pProject;
}

int AProjectManager::closeProject()
{
	delete m_pProject;
	m_pProject = nullptr;

	return 0;
}

AProject * AProjectManager::createProject(const std::string & project_path)
{
	if(closeProject())
		return nullptr;

	string dir_path, fname;
	split_file_path(project_path, dir_path, fname);

	m_pProject = new AProject(fname, dir_path);
	saveProject();

	return m_pProject;
}

AError AProjectManager::saveProject() const
{
	if(!project())
		return AError(AT_ERROR_NO_ACTIVE_PROJECT);

	//Create XML-structure of project file
	xmlDocPtr doc = xmlNewDoc(BAD_CAST XML_DEFAULT_VERSION);
    xmlNodePtr root_node = xmlNewNode(NULL, BAD_CAST "at_project");
	xmlNodeSetContent(root_node, BAD_CAST "");
	xmlDocSetRootElement(doc, root_node);

	//Serialize project tree
	project()->serialize(root_node);

	//Write it
	xmlSetDocCompressMode(doc, 0);

	string project_file_path = project()->projectDir() + "/" + project()->fileName();
	xmlSaveFormatFile(project_file_path.c_str(), doc, 1);
    xmlFreeDoc(doc);

	return AError();
}

AProject * AProjectManager::openProject(const std::string & path)
{
	if(closeProject())
		return nullptr;


	xmlDocPtr doc = xmlParseFile(path.c_str());
	if(!doc)
		return nullptr;

	xmlNodePtr cur = xmlDocGetRootElement(doc);

	string dir_path, fname;
	split_file_path(path, dir_path, fname);

	m_pProject = new AProject();

	m_pProject->setFileName(fname);
	m_pProject->setProjectDir(dir_path);

	m_pProject->deserialize(cur);

	xmlFreeDoc(doc);
	xmlCleanupParser();

	return m_pProject;
}

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

void AProject::documentsWithExtension(std::vector<const ADocumentProjectNode*> & doc_nodes, const std::string & ext) const
{
	m_pRootNode->getDocumentNodesWithExtension(doc_nodes, ext);
}

std::shared_ptr<EDFDDocument> AProject::commonEDFD(AError * err) const
{
	//Get all EDFD document nodes
	vector<const ADocumentProjectNode*> edfd_nodes;
	documentsWithExtension(edfd_nodes, "edfd");

	//Load documents into RAM
	vector<shared_ptr<EDFDDocument>> edfd_docs;
	for(auto doc_node : edfd_nodes)
	{
		shared_ptr<EDFDDocument> new_doc(new EDFDDocument());
		new_doc->loadFromFile(mProjectDir + "/" + doc_node->name());
		edfd_docs.push_back(new_doc);
	}

	//Build detalization links
	for(auto & doc : edfd_docs)
	{
		if(doc->isDetalized())
			doc->buildDetalizationLinks(edfd_docs);
	}

	//Find top-level diagramm - the one left is it

	//Check that it is unique
	return edfd_docs[0];	///!!!!!!!!!!!!!!!!!!!
	if(edfd_docs.size() > 1)
	{
		if(err)
			*err = AError(AT_ERROR_PROJECT_DATA, "More than one EDFD diagramm are top-level, must be only one.");
		return nullptr;
	}

	//Perform detalization

	shared_ptr<EDFDDocument> detailed_doc;

	if(err)
		*err = AError();

	return detailed_doc;
}

ADocumentProjectNode * AProject::addDocument(ADocument * doc)
{
	ADocumentProjectNode * new_node = new ADocumentProjectNode(doc);
	m_pRootNode->addChild(new_node);
	return new_node;
}

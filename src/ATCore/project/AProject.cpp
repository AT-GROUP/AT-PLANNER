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

	//Save current detailed EDFD
	if(m_pDetailEDFD)
	{
		xmlNode * detailed_edfd = xmlNewChild(root_node, NULL, BAD_CAST "detailed_edfd", BAD_CAST "");
		xmlNewProp(detailed_edfd, BAD_CAST "filename" , BAD_CAST "main.edfd");
		m_pDetailEDFD->saveToFile(projectDir() + "/main.edfd");
	}
}

AError AProject::deserialize(xmlNodePtr root_node)
{
	auto cproject_name = xml_prop(root_node, "name");
	setName(string(cproject_name));

	xmlNode * project_tree_node = child_for_path(root_node, "project_root_node");
	m_pRootNode->deserialize(project_tree_node);

	xmlNode * detailed_edfd = child_for_path(root_node, "detailed_edfd");
	if(detailed_edfd)
	{
		m_pDetailEDFD.reset(new EDFDDocument());
		auto cfilename = xml_prop(detailed_edfd, "filename");

		m_pDetailEDFD->loadFromFile(projectDir() + "/" + string(cfilename));
	}

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

void AProject::removeDocumentsWithExtension(const std::string & ext)
{
	m_pRootNode->removeDocumentsWithExtension(ext);
}

struct DFDHierarchyNode
{
	DFDHierarchyNode(const shared_ptr<EDFDDocument> & _doc)
		:doc(_doc)
	{}

	~DFDHierarchyNode()
	{
		for(auto c : children)
			delete c;
	}

	bool detailWith(const shared_ptr<EDFDDocument> & _doc)
	{
		if(doc->isDetalizedWith(_doc))
		{
			DFDHierarchyNode * new_child = new DFDHierarchyNode(_doc);
			children.push_back(new_child);
			return true;
		}
		else
		{
			for(auto c : children)
			{
				if(c->detailWith(_doc))
				{
					return true;
				}
			}

			return false;
		}
	}

	void merge()
	{
		for(auto c : children)
		{
			c->merge();

			//Merge documents
			doc->mergeWith(c->doc);
		}
	}

	shared_ptr<EDFDDocument> doc;
	vector<DFDHierarchyNode*> children;
};

void AProject::buildCommonEDFD(AError * err) const
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
		{
			AError res = doc->buildDetalizationLinks(edfd_docs);
			if(!res.OK())
			{
				AError::criticalErrorOccured(res);
				return;
			}
		}
	}

	//Build detalization tree
	
	DFDHierarchyNode * root_node = new DFDHierarchyNode(*edfd_docs.begin());
	edfd_docs.erase(edfd_docs.begin());

	while(!edfd_docs.empty())
	{
		bool something_added = false;
		auto it = edfd_docs.begin();

		while(it != edfd_docs.end())
		{
			//Check that current document can be detalized with root node
			if((*it)->isDetalizedWith(root_node->doc))
			{
				//Create top-level node
				DFDHierarchyNode * new_root = new DFDHierarchyNode(*it);
				
				//Add current root to it's children
				new_root->children.push_back(root_node);

				root_node = new_root;

				//Remove doc from src list
				
				something_added = true;
			}
			else
			{
				something_added = root_node->detailWith(*it);
			}

			if(something_added)
			{
				edfd_docs.erase(it);
				break;
			}
			else
				++it;
		}

		if(!something_added)
		{
			AError::criticalErrorOccured(AError(AT_ERROR_PROJECT_DATA, "Invalid EDFD Hierarchy structure, cannon build detailed diagramm. Maybe bore than one EDFD diagramm are top-level, must be only one."));
			return;
		}
	}

	//Recursively merge tree children
	root_node->merge();
	m_pDetailEDFD = root_node->doc;

	//Delete tree structure
	delete root_node;

	if(err)
		*err = AError();

	//For building IDs!
	m_pDetailEDFD->saveToFile(projectDir() + "/main.cache.edfd");
}

std::shared_ptr<EDFDDocument> AProject::commonEDFD(AError * err)
{
	if(!m_pDetailEDFD)
		buildCommonEDFD(err);

	return m_pDetailEDFD;
}

ADocumentProjectNode * AProject::addDocument(ADocument * doc)
{
	ADocumentProjectNode * new_node = new ADocumentProjectNode(doc);
	m_pRootNode->addChild(new_node);
	return new_node;
}

ADocumentProjectNode* AProject::findDocumentNode(const std::string & doc_name)
{
	return m_pRootNode->findDocumentNode(doc_name);
}

std::string AProject::documentPath(const ADocumentProjectNode * doc_node) const
{
	return mProjectDir + "/" + doc_node->name();
}

const ADocumentProjectNode * AProject::architectureDocument(AError * err) const
{
	vector<const ADocumentProjectNode*> archs;
	documentsWithExtension(archs, "arch");

	if(archs.size() == 0)
	{
		if(err)
			*err = AError(AT_ERROR_PROJECT_DATA, "Architecture docs not found.");
		return nullptr;
	}
	else if(archs.size() > 1)
	{
		if(err)
		*err = AError(AT_ERROR_PROJECT_DATA, "There must be only 1 architecture document.");
		return nullptr;
	}

	return archs[0];
}

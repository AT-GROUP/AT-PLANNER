
#ifndef ATCore_AProject_h
#define ATCore_AProject_h

#include "../ANamedObject.h"
#include "../AError.h"
#include "../edfd/EDFDDocument.h"
#include <string>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <memory>
#include <vector>

class ARootProjectNode;
class ADocumentProjectNode;

class AT_CORE_API AProject : public ANamedObject
{
public:
	AProject(const std::string & project_name = "", const std::string & project_dir = "");
	ARootProjectNode * rootNode();
	
	/*
	Saves and load project and all it's files.
	*/
	void serialize(xmlNodePtr root_node) const;
	AError deserialize(xmlNodePtr root_node);

	/*
	Returns project dir. Useful for creating new files to
	get target dir.
	*/
	std::string projectDir() const;
	void setProjectDir(const std::string & dir);


	const std::string & fileName() const;
	void setFileName(std::string & f_name);

	/*
	Returns true if something has unsaved chanes.
	*/
	bool hasUnsavedChanges() const;

	/*
	Collects all documents with given extension into give container.
	*/
	void documentsWithExtension(std::vector<const ADocumentProjectNode*> & doc_nodes, const std::string & ext) const;

	/*
	Performs EDFD detalization, creates new document and returns it.
	*/
	void buildCommonEDFD(AError * err = nullptr) const;

	std::shared_ptr<EDFDDocument> commonEDFD(AError * err = nullptr);
	/*
	Adds document to project, creates document node
	in project root and returns created node.
	*/
	ADocumentProjectNode * addDocument(ADocument * doc);

	/*
	Searches for document node in the project tree.
	*/
	ADocumentProjectNode* findDocumentNode(const std::string & doc_name);

	//
	std::string documentPath(ADocumentProjectNode * doc_node) const;
private:
	ARootProjectNode * m_pRootNode;
	//AProjectNode * m_pProject;
	/*
	Path to dir where project main file is. Is absolute and
	is filled on project opening.
	*/
	std::string mProjectDir;

	/*
	Project filename with extension.
	*/
	std::string mProjectFileName;

	mutable std::shared_ptr<EDFDDocument> m_pDetailEDFD;
};

#endif

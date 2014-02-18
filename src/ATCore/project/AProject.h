
#ifndef ATCore_AProject_h
#define ATCore_AProject_h

#include "../ANamedObject.h"
#include <string>
#include <libxml/tree.h>
#include <libxml/parser.h>

class ARootProjectNode;

class AT_CORE_API AProject : public ANamedObject
{
public:
	AProject(const std::string & project_name = "", const std::string & project_dir = "");
	ARootProjectNode * rootNode();
	
	/*
	Saves and load project and all it's files.
	*/
	void serialize(xmlNodePtr root_node) const;
	void deserialize(xmlNodePtr root_node);

	/*
	Returns project dir. Useful for creating new files to
	get target dir.
	*/
	std::string projectDir() const;
	void setProjectDir(const std::string & dir);

	/*
	Returns true if something has unsaved chanes.
	*/
	bool hasUnsavedChanges() const;

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
};

#endif

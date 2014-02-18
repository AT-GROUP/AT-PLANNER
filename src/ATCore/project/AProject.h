
#ifndef ATEnvironment_USProject_h
#define ATEnvironment_USProject_h

#include "../core/ANamedObject.h"
#include <string>
#include <libxml/tree.h>
#include <libxml/parser.h>

class ARootProjectNode;

class AProject : public ANamedObject
{
public:
	AProject(const char * project_name, const char * project_dir);
	ARootProjectNode * rootNode();
	
	/*
	Saves project and all it's files.
	*/
	void save();
	void saveChanges();
	void openProject(xmlNodePtr doc);

	/*
	Returns project dir. Useful for creating new files to
	get target dir.
	*/
	std::string projectDir();
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

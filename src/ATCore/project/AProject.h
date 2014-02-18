
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


#ifndef ATEnvironment_USProject_h
#define ATEnvironment_USProject_h

#include "../core/ANamedObject.h"
#include <string>

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

	/*
	Returns project dir. Useful for creating new files to
	get target dir.
	*/
	std::string projectDir();
private:
	ARootProjectNode * m_pRootNode;
	
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

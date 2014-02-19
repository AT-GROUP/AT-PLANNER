
#ifndef ATCore_AProjectManager_h
#define ATCore_AProjectManager_h

#include "../config.h"
#include "../AError.h"
#include <string>

class AProject;

class AT_CORE_API AProjectManager
{
public:
	AProjectManager();
	AProject * project() const;

	virtual int closeProject();
	AProject * createProject(const std::string & project_path);
	AError saveProject() const;
	AProject * openProject(const std::string & path);
private:
	AProject * m_pProject;
};

#endif

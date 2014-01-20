#ifndef ATENVIRONMENT_H
#define ATENVIRONMENT_H

#include "ui_ATEnvironment.h"
#include "AConsoleWidget.h"
#include <ATCore/AFile.h>
#include <ATGUI/AEditor.h>
#include <QtWidgets/QMainWindow>
#include <memory>

class AProject;
class AGroupProjectNode;
class ATApplication;

class ATEnvironment : public QMainWindow
{
	Q_OBJECT

public:
	ATEnvironment(ATApplication * app, QWidget *parent = 0);
	virtual ~ATEnvironment();
	
	/*
	Displays given project.
	*/
	void displayProject(AProject * _project);

	/*
	Closes current project. Returns 0 if after execution
	no project is displayed.
	*/
	int closeProject();

	/*
	Updates window title due to currently loaded project.
	*/
	void updateWindowTitle();

public slots:
	void createNewProject();
	void createNewFile(AQProjectNode * project_parent_node);
	void openFile(const std::string & file_name);
	void openFile(AFile * file);
private:
	Ui::ATEnvironmentClass ui;
	AProject * m_pProject;
	ATApplication * m_pApplication;
	//Registered extensions
//	std::map<AFile::Type, AAbstractEditorInitializer*> mEditorsFactory;
};

#endif // ATENVIRONMENT_H

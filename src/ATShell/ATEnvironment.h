#ifndef ATENVIRONMENT_H
#define ATENVIRONMENT_H

#include <ATCore/project/AProjectManager.h>
#include <QtWidgets/QMainWindow>
#include "ui_ATEnvironment.h"
#include <libxml/tree.h>
#include <libxml/parser.h>


class AProject;
class AGroupProjectNode;
class ATApplication;

class ATEnvironment : public QMainWindow, public AProjectManager
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
	virtual int closeProject() override;

	//void parseDocument(xmlNodePtr _ptr, AProjectNode * _node);

public slots:
	void createNewProject();
	void createNewFile(AQProjectNode * project_parent_node);
	void openProject();
	void openNodeDocument(ADocumentProjectNode * doc_node);
private:
	Ui::ATEnvironmentClass ui;
	ATApplication * m_pApplication;
};

#endif // ATENVIRONMENT_H

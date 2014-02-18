#ifndef ATENVIRONMENT_H
#define ATENVIRONMENT_H

#include <QtWidgets/QMainWindow>
#include "ui_ATEnvironment.h"
#include <libxml/tree.h>
#include <libxml/parser.h>


class AProject;
class AGroupProjectNode;

class ATEnvironment : public QMainWindow
{
	Q_OBJECT

public:
	ATEnvironment(QWidget *parent = 0);
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

	void parseDocument(xmlNodePtr _ptr, AProjectNode * _node);

	/*
	Updates window title due to currently loaded project.
	*/
	void updateWindowTitle();
public slots:
	void createNewProject();
	void createNewFile(AQProjectNode * project_parent_node);
	void openFile(AFile * file);
	void saveRecentChanges();
	void openProject();
private:
	Ui::ATEnvironmentClass ui;
	AProject * m_pProject;
};

#endif // ATENVIRONMENT_H

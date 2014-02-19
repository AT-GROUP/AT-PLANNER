#ifndef APROJECTEXPLORER_H
#define APROJECTEXPLORER_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QTreeWidgetItem>
#include <QtWidgets/QTreeWidget>
#include "ui_AProjectExplorer.h"

class AGroupProjectNode;

class AProjectExplorer : public QWidget
{
	Q_OBJECT

public:
	AProjectExplorer(QWidget *parent = 0);
	~AProjectExplorer();
	void loadProjectTree(ARootProjectNode * root_node);
signals:
	void createNewFileRequested(AQProjectNode * project_parent_node);
	void openNodeFileRequested(ADocumentProjectNode * file);
private:
	Ui::AProjectExplorer ui;
};

#endif // APROJECTEXPLORER_H

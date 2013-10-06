#include "AProjectExplorer.h"
#include "project/AProjectNode.h"
#include "core/AFile.h"

//============================AProjectExplorer================================
AProjectExplorer::AProjectExplorer(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	connect(ui.treeProject, &AQProjectTreeWidget::createNewFileRequested, this, &AProjectExplorer::createNewFileRequested);
	connect(ui.treeProject, &AQProjectTreeWidget::openFileRequested, this, &AProjectExplorer::openFileRequested);
}

AProjectExplorer::~AProjectExplorer()
{

}

void AProjectExplorer::loadProjectTree(ARootProjectNode * root_node)
{
	ui.treeProject->loadProjectTree(root_node);
}

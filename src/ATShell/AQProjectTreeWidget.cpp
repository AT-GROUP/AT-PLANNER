#include "AQProjectTreeWidget.h"
#include <ATCore/project/AProjectNode.h>
#include <ATCore/AFile.h>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMessageBox>

//============================AProjectExplorer================================
AQProjectNode::AQProjectNode(AProjectNode * project_node, QTreeWidgetItem * parent)
	:QTreeWidgetItem(parent), m_pProjectNode(project_node)
{
	setText(0, QString("%1").arg(project_node->name()));
	setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable);

	updateIcon();
}

int AQProjectNode::type()
{
	return m_pProjectNode->type();
}

AProjectNode * AQProjectNode::projectNode()
{
	return m_pProjectNode;
}

void AQProjectNode::updateIcon()
{
/*	switch(m_pProjectNode->type())
	{
	case AProjectNode::Group:
		if(isExpanded())
			setIcon(0, QIcon(":/SurveyViewer/resources/icons/project_tree/group_expanded.ico"));
		else
			setIcon(0, QIcon(":/SurveyViewer/resources/icons/project_tree/group.ico"));
		break;
	case AProjectNode::ProjectRoot:
		setIcon(0, QIcon(":/SurveyViewer/resources/icons/project_tree/project.ico"));
		break;
	case AProjectNode::File:
		setIcon(0, QIcon(":/SurveyViewer/resources/icons/project_tree/file.ico"));
		break;
	default:
		break;
	}	*/
}


//=====================Tree=========================
AQProjectTreeWidget::AQProjectTreeWidget(QWidget *parent)
	: QTreeWidget(parent), m_pCurrentSelection(0), m_pProjectRoot(0)
{
	//Setup context menu
	setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this, &AQProjectTreeWidget::customContextMenuRequested, this, &AQProjectTreeWidget::showContextMenu);
	//connect(this, &AQProjectTreeWidget::itemChanged, this, &AQProjectTreeWidget::onTreeItemChanged);

	//Auto update icon
	connect(this, &AQProjectTreeWidget::itemExpanded, [=](QTreeWidgetItem * item){((AQProjectNode*)item)->updateIcon();});
	connect(this, &AQProjectTreeWidget::itemCollapsed, [=](QTreeWidgetItem * item){((AQProjectNode*)item)->updateIcon();});
}

AQProjectTreeWidget::~AQProjectTreeWidget()
{

}

void AQProjectTreeWidget::loadProjectTree(ARootProjectNode * project_root)
{
	m_pProjectRoot = project_root;

	updateData();
}

void AQProjectTreeWidget::updateData()
{
	if(m_pProjectRoot)
	{
		//Create root project node
		AQProjectNode * root_node = new AQProjectNode(m_pProjectRoot, 0);
		addTopLevelItem(root_node);

		createItemSubtree(root_node, m_pProjectRoot);
	}
}

void AQProjectTreeWidget::createItemSubtree(AQProjectNode * tw_node, AProjectNode * prj_node)
{
	tw_node->setText(0, QString("%1").arg(prj_node->name()));

	for(auto c : prj_node->mChildren)
	{
		AQProjectNode * new_node = new AQProjectNode(c, tw_node);
		createItemSubtree(new_node, c);
	}
}

void AQProjectTreeWidget::showContextMenu(const QPoint &pos)
{
	//Determine selection
	auto selected_items = selectedItems();
	AQProjectNode * selected_item = 0;
	if(selected_items.size() == 1)
		selected_item = (AQProjectNode*)selected_items[0];

	QMenu contextMenu("Context menu", this);

	if(selected_item)
	{
		bool item_specific_actions = false;

		if(selected_item->type() == AProjectNode::File)
		{
			AFile * file = ((AFileProjectNode*)selected_item->projectNode())->file();
			QAction * actionOpen = new QAction(QIcon(":/SurveyViewer/resources/icons/project_tree/open_file.ico"), "Open", this);
			contextMenu.addAction(actionOpen);
			connect(actionOpen, &QAction::triggered, [=](){this->openFileRequested(file);});
			
			item_specific_actions = true;
		}


		if(item_specific_actions)
			contextMenu.addSeparator();

		//Add action, if it is group
		if(dynamic_cast<AGroupProjectNode*>(selected_item->projectNode()))
		{
			QMenu * menuAdd = new QMenu("Add", this);

			QAction * actionAddGroup = new QAction(QIcon(":/SurveyViewer/resources/icons/project_tree/new_group.ico"), "New Group", menuAdd);
			menuAdd->addAction(actionAddGroup);
			connect(actionAddGroup, &QAction::triggered, this, &AQProjectTreeWidget::onAddGroupItemClicked);

			QAction * actionAddNewFile = new QAction(QIcon(":/SurveyViewer/resources/icons/project_tree/file.ico"), "New Item...", menuAdd);
			menuAdd->addAction(actionAddNewFile);
			connect(actionAddNewFile, &QAction::triggered, [=](){this->createNewFileRequested(selected_item);});

			QAction * actionAddExistingFile = new QAction(QIcon(":/SurveyViewer/resources/icons/project_tree/file.ico"), "Existing Item...", menuAdd);
			menuAdd->addAction(actionAddExistingFile);

			contextMenu.addMenu(menuAdd);

			contextMenu.addSeparator();
		}

		//Common actions
		QAction * actionRename = new QAction(QIcon(":/SurveyViewer/resources/icons/project_tree/rename.ico"), "Rename", this);
		contextMenu.addAction(actionRename);
		connect(actionRename, &QAction::triggered, this, &AQProjectTreeWidget::onRenameItemClicked);

		//Remove action only if not root
		if(selected_item->type() != AProjectNode::ProjectRoot)
		{
			QAction * actionRemove = new QAction(QIcon(":/SurveyViewer/resources/icons/project_tree/remove.ico"), "Remove", this);
			contextMenu.addAction(actionRemove);
			connect(actionRemove, &QAction::triggered, this, &AQProjectTreeWidget::onRemoveItemClicked);
		}
	}

	m_pCurrentSelection = selected_item;

	contextMenu.exec(viewport()->mapToGlobal(pos));
}

void AQProjectTreeWidget::onRenameItemClicked()
{
	editItem(m_pCurrentSelection);
}

void AQProjectTreeWidget::onAddGroupItemClicked()
{
	AGroupProjectNode * new_group = new AGroupProjectNode("new_group");
	m_pCurrentSelection->projectNode()->addChild(new_group);

	AQProjectNode * tw_node = new AQProjectNode(new_group, m_pCurrentSelection);
	if(!m_pCurrentSelection->isExpanded())
		m_pCurrentSelection->setExpanded(true);

	editItem(tw_node);
}

void AQProjectTreeWidget::onRemoveItemClicked()
{
	auto res = QMessageBox::warning(this, "Confirm", QString("Are you sure you want to remove %1?").arg(m_pCurrentSelection->projectNode()->name()), QMessageBox::Ok | QMessageBox::Cancel);

	if(res == QMessageBox::Ok)
	{
		AQProjectNode * remove_parent = (AQProjectNode*)m_pCurrentSelection->parent();

		remove_parent->projectNode()->removeChild(m_pCurrentSelection->projectNode());
		remove_parent->removeChild(m_pCurrentSelection);
	}
}

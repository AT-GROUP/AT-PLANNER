#ifndef AQPROJECTTREEWIDGET_H
#define AQPROJECTTREEWIDGET_H

#include <QTreeWidget>

class AProjectNode;
class ARootProjectNode;
class AGroupProjectNode;
class AFile;

class AQProjectNode : public QTreeWidgetItem
{
public:
	AQProjectNode(AProjectNode * project_node, QTreeWidgetItem * parent);
	int type();
	AProjectNode * projectNode();
	void updateIcon();
private:
	AProjectNode * m_pProjectNode;
};

class AQProjectTreeWidget : public QTreeWidget
{
	Q_OBJECT

public:
	AQProjectTreeWidget(QWidget *parent);
	~AQProjectTreeWidget();
	void loadProjectTree(ARootProjectNode * project_root);
	void updateData();
	void createItemSubtree(AQProjectNode * tw_node, AProjectNode * prj_node);
private slots:
	void showContextMenu(const QPoint &pos);
	void onRenameItemClicked();
	void onAddGroupItemClicked();
	void onRemoveItemClicked();
signals:
	void createNewFileRequested(AQProjectNode * project_parent_node);
	void openFileRequested(AFile * file);
private:
	AQProjectNode * m_pCurrentSelection;
	ARootProjectNode * m_pProjectRoot;
};

#endif // AQPROJECTTREEWIDGET_H

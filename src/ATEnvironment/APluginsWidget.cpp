#include "APluginsWidget.h"
#include <ATCore/plugin/APluginManager.h>
#include <QtWidgets/QTreeWidgetItem>

APluginsWidget::APluginsWidget(APluginManager * plug_mgr, QWidget *parent)
	: QWidget(parent), m_pPlugMgr(plug_mgr)
{
	ui.setupUi(this);

	updateData();
}

APluginsWidget::~APluginsWidget()
{

}

void APluginsWidget::updateData()
{
	ui.treePlugins->clear();

	static const char * TypeNames[] = {"Utility Plugins", "Editor Plugins"};

	QList<QTreeWidgetItem *> group_items;
	for (int i = 0; i < static_cast<int>(APlugin::Type::Count); ++i)
	{
		QString type_name = QString::fromUtf8(TypeNames[i]);
		auto group_item = new QTreeWidgetItem((QTreeWidget*)0, QStringList(type_name));
		
		for(auto & plugin : m_pPlugMgr->plugins(static_cast<APlugin::Type>(i)))
		{
			APlugin * plug = plugin->plugin();

			QStringList cols;
			cols.append(QString::fromStdString(plug->name()));
			cols.append(QString::fromStdString(plug->description()));
			cols.append(QString::fromWCharArray(plugin->path()));

			auto plugin_item = new QTreeWidgetItem((QTreeWidget*)0, cols);

			group_item->addChild(plugin_item);
		}

		group_items.append(group_item);
	}
	
	ui.treePlugins->insertTopLevelItems(0, group_items);

	for(auto gi : group_items)
		gi->setExpanded(true);
}

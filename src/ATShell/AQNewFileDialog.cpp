#include "AQNewFileDialog.h"
#include <ATCore/plugin/APluginManager.h>
#include <QtCore/QDir>
#include <string>

using namespace std;

AQNewFileDialog::AQNewFileDialog(APluginManager * pmgr, QWidget *parent)
	: QDialog(parent), mSelectedTypeEditor(nullptr)
{
	ui.setupUi(this);

	connect(ui.bnOK, &QPushButton::clicked, this, &AQNewFileDialog::accept);
	connect(ui.bnCancel, &QPushButton::clicked, this, &AQNewFileDialog::close);

	//Display avalible file list based on loaded editors
	auto editors = pmgr->plugins(APlugin::Type::Editor);

	QListWidgetItem * first_item = nullptr;
	for(auto e : editors)
	{
		auto ed_plugin = static_cast<AEditorPlugin*>(e->plugin());
		mEditors.push_back(ed_plugin);

		string item_descr = ed_plugin->documentDescription() + " (." + ed_plugin->documentExtension() + ")";

		QListWidgetItem * item = new QListWidgetItem(QString::fromStdString(item_descr));
		item->setData(Qt::UserRole, mEditors.size() - 1);

		ui.listAvalibleFiles->addItem(item);
		
		if(!first_item)
			first_item = item;
	}

	//Save selection
	connect(ui.listAvalibleFiles, &QListWidget::itemClicked, [=](QListWidgetItem * item)
		{
			int plugin_index =  item->data(Qt::UserRole).toInt();
			mSelectedTypeEditor = mEditors[plugin_index];

			QFileInfo fi(ui.edFileName->text());
			QString new_name = fi.completeBaseName() + "." + QString::fromStdString(mSelectedTypeEditor->documentExtension());
			ui.edFileName->setText(new_name);
			ui.edFileName->setSelection(0, fi.completeBaseName().length());
			ui.edFileName->setFocus();
	});

	//Select 1st item
	if(first_item)
	{
		ui.listAvalibleFiles->setItemSelected(first_item, true);
		emit ui.listAvalibleFiles->itemClicked(first_item);
	}
}

AQNewFileDialog::~AQNewFileDialog()
{

}

QString AQNewFileDialog::fileName()
{
	return ui.edFileName->text();
}

AEditorPlugin * AQNewFileDialog::selectedTypeEditor() const
{
	return mSelectedTypeEditor;
}

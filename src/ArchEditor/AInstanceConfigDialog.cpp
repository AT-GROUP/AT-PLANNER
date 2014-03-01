#include "AInstanceConfigDialog.h"

AInstanceConfigDialog::AInstanceConfigDialog(APIKConfigInstance & config, QWidget *parent)
	: QDialog(parent), mConfig(config)
{
	ui.setupUi(this);

	connect(ui.bnOK, &QPushButton::clicked, this, &AInstanceConfigDialog::accept);
	connect(ui.bnCancel, &QPushButton::clicked, this, &AInstanceConfigDialog::reject);

	//Display params
	updateData();
}

AInstanceConfigDialog::~AInstanceConfigDialog()
{

}

void AInstanceConfigDialog::saveConfig()
{

}

void AInstanceConfigDialog::updateData()
{
	ui.tableParams->clear();

	ui.tableParams->setRowCount(mConfig.params().size());

	int row = 0;
	for(auto & param : mConfig.params())
	{
		QTableWidgetItem * name_item = new QTableWidgetItem(QString::fromStdString(param.name));
		ui.tableParams->setItem(row, 0, name_item);
		++row;
	}
}

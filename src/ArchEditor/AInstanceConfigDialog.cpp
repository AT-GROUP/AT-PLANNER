#include "AInstanceConfigDialog.h"

AInstanceConfigDialog::AInstanceConfigDialog(APIKConfig & config, QWidget *parent)
	: QDialog(parent), mConfig(config)
{
	ui.setupUi(this);

	connect(ui.bnOK, &QPushButton::clicked, this, &AInstanceConfigDialog::accept);
	connect(ui.bnCancel, &QPushButton::clicked, this, &AInstanceConfigDialog::reject);
}

AInstanceConfigDialog::~AInstanceConfigDialog()
{

}

void AInstanceConfigDialog::saveConfig()
{

}

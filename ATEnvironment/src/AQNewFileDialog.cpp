#include "AQNewFileDialog.h"

AQNewFileDialog::AQNewFileDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect(ui.bnOK, &QPushButton::clicked, this, &AQNewFileDialog::accept);
	connect(ui.bnCancel, &QPushButton::clicked, this, &AQNewFileDialog::close);
}

AQNewFileDialog::~AQNewFileDialog()
{

}

QString AQNewFileDialog::fileName()
{
	return ui.edFileName->text();
}

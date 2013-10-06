#include "AQNewProjectDialog.h"
#include <QtWidgets/QFileDialog>

AQNewProjectDialog::AQNewProjectDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect(ui.bnOK, &QPushButton::clicked, this, &AQNewProjectDialog::accept);
	connect(ui.bnCancel, &QPushButton::clicked, this, &AQNewProjectDialog::close);
	connect(ui.bnSelectDirectory, &QPushButton::clicked, this, &AQNewProjectDialog::openProjectDirectory);
}

AQNewProjectDialog::~AQNewProjectDialog()
{

}

void AQNewProjectDialog::openProjectDirectory()
{
	QString str = QFileDialog::getExistingDirectory(this, "Select project directory", ui.edDirectory->text());

	if(str != "")
		ui.edDirectory->setText(str);
}

QString AQNewProjectDialog::projectDir()
{
	return ui.edDirectory->text();
}

QString AQNewProjectDialog::projectName()
{
	return ui.edProjectName->text();
}

#ifndef AQNEWPROJECTDIALOG_H
#define AQNEWPROJECTDIALOG_H

#include <QDialog>
#include "ui_AQNewProjectDialog.h"

class AQNewProjectDialog : public QDialog
{
	Q_OBJECT

public:
	AQNewProjectDialog(QWidget *parent = 0);
	~AQNewProjectDialog();
	void openProjectDirectory();
	QString projectDir();
	QString projectName();
private:
	Ui::AQNewProjectDialog ui;
};

#endif // AQNEWPROJECTDIALOG_H

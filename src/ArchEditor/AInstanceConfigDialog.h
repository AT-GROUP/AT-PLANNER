#ifndef AINSTANCECONFIGDIALOG_H
#define AINSTANCECONFIGDIALOG_H

#include <QDialog>
#include "ui_AInstanceConfigDialog.h"
#include <ATCore/architecture/AArchElement.h>

class AInstanceConfigDialog : public QDialog
{
	Q_OBJECT

public:
	AInstanceConfigDialog(APIKConfig & config, QWidget *parent = 0);
	~AInstanceConfigDialog();
	void saveConfig();
private:
	Ui::AInstanceConfigDialog ui;
	APIKConfig & mConfig;
};

#endif // AINSTANCECONFIGDIALOG_H

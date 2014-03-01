#ifndef AINSTANCECONFIGDIALOG_H
#define AINSTANCECONFIGDIALOG_H

#include <QDialog>
#include "ui_AInstanceConfigDialog.h"
#include <ATCore/architecture/AArchElement.h>

class AInstanceConfigDialog : public QDialog
{
	Q_OBJECT

public:
	AInstanceConfigDialog(APIKConfigInstance & config, QWidget *parent = 0);
	~AInstanceConfigDialog();
	void saveConfig();
	void updateData();
private:
	Ui::AInstanceConfigDialog ui;
	APIKConfigInstance & mConfig;
};

#endif // AINSTANCECONFIGDIALOG_H

#ifndef AQNEWFILEDIALOG_H
#define AQNEWFILEDIALOG_H

#include <QDialog>
#include "ui_AQNewFileDialog.h"

class AQNewFileDialog : public QDialog
{
	Q_OBJECT

public:
	AQNewFileDialog(QWidget *parent = 0);
	~AQNewFileDialog();
	QString fileName();
private:
	Ui::AQNewFileDialog ui;
};

#endif // AQNEWFILEDIALOG_H

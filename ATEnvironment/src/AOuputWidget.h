#ifndef AOUPUTWIDGET_H
#define AOUPUTWIDGET_H

#include <QWidget>
#include "ui_AOuputWidget.h"

class AOuputWidget : public QWidget
{
	Q_OBJECT

public:
	AOuputWidget(QWidget *parent = 0);
	~AOuputWidget();

private:
	Ui::AOuputWidget ui;
};

#endif // AOUPUTWIDGET_H

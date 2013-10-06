#ifndef APLANNERWIDGET_H
#define APLANNERWIDGET_H

#include <QWidget>
#include "ui_APlannerWidget.h"

class APlannerWidget : public QWidget
{
	Q_OBJECT

public:
	APlannerWidget(QWidget *parent = 0);
	~APlannerWidget();

private:
	Ui::APlannerWidget ui;
};

#endif // APLANNERWIDGET_H

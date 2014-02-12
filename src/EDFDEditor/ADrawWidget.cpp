#include "adrawwidget.h"

ADrawWidget::ADrawWidget(QWidget *parent)
    : QListWidget(parent)
{
    QListWidgetItem * item_1 = new QListWidgetItem("Test1");
    addItem(item_1);

	QListWidgetItem * item_2 = new QListWidgetItem("Test2");
    addItem(item_2);

	QListWidgetItem * item_3 = new QListWidgetItem("Test3");
    addItem(item_3);

	QListWidgetItem * item_4 = new QListWidgetItem("Test5");
    addItem(item_4);

    //setDragDropMode(QAbstractItemView::DragOnly);
}

#include "adrawwidget.h"

ADrawWidget::ADrawWidget(QWidget *parent)
    : QListWidget(parent)
{
    QListWidgetItem * item_1 = new QListWidgetItem("Entity");
    addItem(item_1);

	QListWidgetItem * item_2 = new QListWidgetItem("Function");
    addItem(item_2);

	QListWidgetItem * item_3 = new QListWidgetItem("Storage");
    addItem(item_3);

	QListWidgetItem * item_4 = new QListWidgetItem("NF Function");
    addItem(item_4);

    //setDragDropMode(QAbstractItemView::DragOnly);
}

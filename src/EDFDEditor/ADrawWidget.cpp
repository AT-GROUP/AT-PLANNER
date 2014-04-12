#include "adrawwidget.h"

ADrawWidget::ADrawWidget(QWidget *parent)
    : QListWidget(parent)
{
    QListWidgetItem * item_1 = new QListWidgetItem("Entity");
	QIcon *ico1 = new QIcon("D:\NewProject1\rectangle.png");
	item_1->setIcon(*ico1);
    addItem(item_1);
	
	QListWidgetItem * item_2 = new QListWidgetItem("Function");
	QPixmap icon2;
	item_2->setIcon(icon2);
    addItem(item_2);

	QListWidgetItem * item_3 = new QListWidgetItem("Storage");
	QPixmap icon3;
	item_3->setIcon(icon3);
    addItem(item_3);

	QListWidgetItem * item_4 = new QListWidgetItem("NF Function");
	QPixmap icon4;
	item_4->setIcon(icon4);
    addItem(item_4);

	QListWidgetItem * item_5 = new QListWidgetItem("Anchor");
	QPixmap icon5;
	item_5->setIcon(icon5);
    addItem(item_5);

    //setDragDropMode(QAbstractItemView::DragOnly);
}

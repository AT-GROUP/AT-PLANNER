#include "ADatastreamWidget.h"

ADatastreamWidget::ADatastreamWidget(QWidget *parent)
{

}

void ADatastreamWidget::insertItem()
{
    QString itemText = QInputDialog::getText(this, tr("Insert Item"),
        tr("Input data for the new item:"));

    if (itemText.isNull())
        return;

    QListWidgetItem *newItem = new QListWidgetItem;
    newItem->setText(itemText);

	this->addItem(newItem);
}

void ADatastreamWidget::removeItem()
{
	if (!this->currentItem())
        return;

	this->takeItem(this->row(this->currentItem()));
}

void  ADatastreamWidget::changeItem()
{
	if (!this->currentItem())
        return;

	QString itemText = QInputDialog::getText(this, tr("Insert Item"),
        tr("Input data for the new item:"), QLineEdit::Normal, this->currentItem()->text());

    if (itemText.isNull() || this->currentItem()->text() == itemText)
        return;

	this->currentItem()->setText(itemText);
}

void ADatastreamWidget::contextMenuEvent(QContextMenuEvent *event)
{
	menu = new QMenu;
	add = new QAction("Add data",this);
	menu->addAction(add);
	change = new QAction("Change this data",this);
	menu->addAction(change);
	del = new QAction("Delete this data",this);
	menu->addAction(del);

	connect(add, SIGNAL(triggered()), this, SLOT(insertItem()));
	connect(del, SIGNAL(triggered()), this, SLOT(removeItem()));
	connect(change, SIGNAL(triggered()), this, SLOT(changeItem()));

	menu->popup(event->globalPos());
}

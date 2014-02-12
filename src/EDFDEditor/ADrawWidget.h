#ifndef ADRAWWIDGET_H
#define ADRAWWIDGET_H

#include <QListWidget>
#include <QtWidgets>

class ADrawWidget : public QListWidget
{
    Q_OBJECT
public:
    ADrawWidget(QWidget *parent = 0);

signals:
	void itemActivated ( QListWidgetItem * item );

public slots:

protected:
	virtual void dragEnterEvent(QDragEnterEvent *event) 
    { 
        event->accept(); 
    }
 
    virtual void dragMoveEvent(QDragMoveEvent *event)
    {
        event->accept();
    }
 
    virtual void dropEvent(QDropEvent *event)
    {
        event->accept();
    }
 
    virtual void mouseMoveEvent(QMouseEvent *event)
    {
        if (!(event->buttons() & Qt::LeftButton)) return;
        if (currentItem() == NULL) return;
 
        QDrag *drag = new QDrag(this);
        QMimeData *mimeData = new QMimeData;
 
        mimeData->setText(currentItem()->text());
        drag->setMimeData(mimeData);

		/*
		для добавление иконки "перемещаемого объекта" дописать тут цикл в зависимости от текста в текущем элементе
        drag->setPixmap(IconFactory::getTablesIcon().pixmap(16,16));

		*/

        drag->start(Qt::CopyAction | Qt::MoveAction);
    }

};

#endif // ADRAWWIDGET_H

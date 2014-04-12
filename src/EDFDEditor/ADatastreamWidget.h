#ifndef DATASTREAM_WIDGET_H
#define DATASTREAM_WIDGET_H

#include <QtWidgets>
#include <QListWidget>

class ADatastreamWidget : public QListWidget
{
    Q_OBJECT
public:
	QMenu *menu;
	QAction *add;
	QAction *change;
	QAction *del;

    ADatastreamWidget(QWidget *parent = 0);

	void contextMenuEvent(QContextMenuEvent *ce);
public slots:
	void insertItem();
    void removeItem();
	void changeItem();
};

#endif // DATASTREAM_WIDGET_H

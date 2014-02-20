
#ifndef AARCHEDITOR_AGDocumentView_H
#define AARCHEDITOR_AGDocumentView_H

#include <QtWidgets/QGraphicsView>

class AArchScene : public QGraphicsScene
{
public:
	AArchScene();

protected:
	//virtual void dragMoveEvent ( QGraphicsSceneDragDropEvent * event ) override;
};

class AGDocumentView : public QGraphicsView
{
public:
	AGDocumentView(QWidget *parent = 0);
protected:
   /* virtual void dragEnterEvent(QDragEnterEvent *event) override;
    virtual void dragMoveEvent(QDragMoveEvent *event) override;
    virtual void dropEvent(QDropEvent *event) override;*/
};

#endif

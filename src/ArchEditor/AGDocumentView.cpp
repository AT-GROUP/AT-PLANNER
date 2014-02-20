
#include "AGDocumentView.h"

//====================AArchScene==========================

AArchScene::AArchScene()
	:QGraphicsScene(0, 0, 300, 300)
{
	
}
/*
void AArchScene::dragMoveEvent(QGraphicsSceneDragDropEvent * event)
{

}
*/
//====================AGDocumentView==========================

AGDocumentView::AGDocumentView(QWidget *parent)
	:QGraphicsView(parent)
{
	setScene(new AArchScene());
	setAcceptDrops(true);
}
/*
void AGDocumentView::dragEnterEvent(QDragEnterEvent *event)
{

}

void AGDocumentView::dragMoveEvent(QDragMoveEvent *event)
{

}

void AGDocumentView::dropEvent(QDropEvent *event)
{

}
*/
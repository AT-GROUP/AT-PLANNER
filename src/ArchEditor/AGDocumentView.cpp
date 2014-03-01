
#include "AGDocumentView.h"
#include "AGArchElement.h"
#include <QtGui/QDragEnterEvent>
#include <QtCore/QMimeData>
#include <QtCore/QDebug>
#include <QtWidgets/QGraphicsItem>
#include <QtWidgets/QGraphicsLineItem>

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
	mLinkCreating.active = false;
}

void AGDocumentView::dragEnterEvent(QDragEnterEvent *event)
{
	event->acceptProposedAction();
}

AGArchGroup * get_intersected_group(QGraphicsScene * scene, QPointF scene_pos)
{
	bool found_group = false;

	auto its = scene->items(scene_pos, Qt::IntersectsItemBoundingRect);
	for(auto i : its)
	{
		auto gr_item = qgraphicsitem_cast<AGArchGroup*>(i);
		if(gr_item)
		{
			return gr_item;
		}
	}

	return nullptr;
}

void AGDocumentView::dragMoveEvent(QDragMoveEvent *event)
{
	auto intersected_group = get_intersected_group(scene(), mapToScene(event->pos()));
	
	if(intersected_group)
		event->acceptProposedAction();
	else
		event->ignore();

	//qDebug() << "move" << scene_pos;
}

void AGDocumentView::dropEvent(QDropEvent *event)
{
	auto intersected_group = get_intersected_group(scene(), mapToScene(event->pos()));
	
	if(intersected_group)
	{
		event->acceptProposedAction();

		auto md = event->mimeData();
		QString text = md->text();
		emit itemAdded(intersected_group, text.toStdString(), event->pos());
	}
	else
		event->ignore();
}

void AGDocumentView::mouseMoveEvent(QMouseEvent *event)
{
	if(mLinkCreating.active)
	{
		QPointF scene_pos = mapToScene(event->pos());
		mLinkCreating.line->setLine(mLinkCreating.startPoint.x(), mLinkCreating.startPoint.y(), scene_pos.x(), scene_pos.y());
	}
	else
	{
		QGraphicsView::mouseMoveEvent(event);
	}
}

void AGDocumentView::mouseReleaseEvent(QMouseEvent *event)
{
	if(mLinkCreating.active)
	{
		mLinkCreating.active = false;
		scene()->removeItem(mLinkCreating.line);

		//Try to find slot item under cursor
		QPointF vp_pos = event->pos();
		auto ites = items(vp_pos.x(), vp_pos.y(), 2, 2);
		
		for(auto it : ites)
		{
			AGSlotElement * slot = dynamic_cast<AGSlotElement*>(it->parentItem());
			if(slot)
			{
				AArchElement * dest = slot->archElement();
				auto slot_name = slot->slotName();
				emit linkCreatingFinished(mLinkCreating.source_item->element(), dest, slot_name);
				break;
			}
		}
	}
	else
	{
		QGraphicsView::mouseReleaseEvent(event);
	}
}

void AGDocumentView::startLinkDragging(AGArchElement * src, QPoint start_point)
{
	mLinkCreating.active = true;

	//Cretate arrow item and remember it
	mLinkCreating.line = new QGraphicsLineItem();
	mLinkCreating.line->setPen(QPen(QBrush(QColor(0, 255, 0)), 2.0));
	mLinkCreating.startPoint = start_point;
	mLinkCreating.source_item = src;
	scene()->addItem(mLinkCreating.line);
}
/*
void AGDocumentView::mousePressEvent(QMouseEvent *event)
{
	QPointF scene_point = mapToScene(event->pos());

	qDebug() << event->pos() << scene_point;

	auto it = itemAt(scene_point.toPoint());
	AGLinkStarter * link_starter = qgraphicsitem_cast<AGLinkStarter*>(it);
	if(link_starter)
	{
		event->ignore();
		qDebug() << "Starting link.";
	}
	else
		QGraphicsView::mousePressEvent(event);
}*/
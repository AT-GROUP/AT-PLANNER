
#include "AGArchElement.h"
#include <ATCore/architecture/AArchElement.h>
#include <ATCore/architecture/AArchElementGroup.h>
#include <QtWidgets/QGraphicsSceneDragDropEvent>
#include <QtGui/QDrag>
#include <QtGui/QPen>
#include <QtWidgets/QWidget>

using namespace std;

const float START_DRAG_DISTANCE = 10.0f;

class AGSlotElement : public QGraphicsItemGroup
{
public:
	AGSlotElement(const APIKInterface::Slot & _slot, QGraphicsItem * parent = 0)
		:QGraphicsItemGroup(parent), mSlot(_slot)
	{
		QGraphicsEllipseItem * ellipse = new QGraphicsEllipseItem(0, 0, 16, 16, this);
		ellipse->setPos(-17, -8);

		QGraphicsTextItem * label = new QGraphicsTextItem(QString::fromStdString(mSlot.name), this);
		label->setPos(-16 - label->boundingRect().width() - 3, - label->boundingRect().height() / 2);
	}

private:
	APIKInterface::Slot mSlot;
};

AGArchFuncElement::AGArchFuncElement(const std::shared_ptr<AArchFuncElement> & _element)
	:QGraphicsItemGroup(), mElement(_element)
{
	//Main form
	auto rect = new QGraphicsRectItem(-50, -25, 100, 50, this);
	setHandlesChildEvents(true);
	
	//Config icon if element has config
	if(mElement->hasConfig())
	{
		QPixmap config_icon(":/icons/resources/icons/config.png");
		config_icon = config_icon.scaled(24, 24);

		QGraphicsPixmapItem * config_item = new QGraphicsPixmapItem(config_icon, this);
		config_item->setPos(- 50 - config_item->boundingRect().width() / 2, - 25 - config_item->boundingRect().height() / 2);
	}

	//Element name
	QGraphicsTextItem * text_item = new QGraphicsTextItem(QString::fromStdString(mElement->name()), this);
	text_item->setPos(- text_item->boundingRect().width() / 2, - text_item->boundingRect().height() / 2);

	//Slots
	float current_height = -25 + 20;
	for(auto & slot : mElement->interfaceDeclaration().inputs)
	{
		AGSlotElement * new_slot = new AGSlotElement(slot, this);
		new_slot->setPos(-50, current_height + new_slot->boundingRect().height() / 2);
		current_height += 18;
	}


	setAcceptDrops(true);
	setPos(mElement->pos().x(), mElement->pos().y());

	setFlag(QGraphicsItem::ItemIsMovable);
}
/*
void AGArchFuncElement::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	mIsDragging = true;
}



void AGArchFuncElement::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton)).length() < START_DRAG_DISTANCE)
	{
        return;
    }
	QPointF new_pos(mElement->pos().x(), mElement->pos().y());
	new_pos += (event->screenPos() - event->buttonDownScreenPos(Qt::LeftButton));

	setPos(new_pos);
}
*/

void AGArchFuncElement::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	QGraphicsItemGroup::mouseReleaseEvent(event);
	/*mIsDragging = false;
*/
	QPointF delta(event->scenePos() - event->buttonDownScenePos(Qt::LeftButton));
	mElement->setPos(mElement->pos() + APoint(delta.x(), delta.y()));

	static_cast<AGArchGroup*>(parentItem())->childGeometryChanged();
}

//=======================Info Element==============================
AGArchInfoElement::AGArchInfoElement(const std::shared_ptr<AArchInfoElement> & _element)
	:QGraphicsItemGroup(), mElement(_element)
{
	auto rect = new QGraphicsEllipseItem(-50, -25, 100, 50, this);
	setHandlesChildEvents(true);

	//Element name
	QGraphicsTextItem * text_item = new QGraphicsTextItem(QString::fromStdString(mElement->name()), this);
	text_item->setPos(- text_item->boundingRect().width() / 2, - text_item->boundingRect().height() / 2);


	setFlag(QGraphicsItem::ItemIsMovable);
}

//=========================Group=================================
AGArchGroup::AGArchGroup(const std::shared_ptr<AArchElementGroup> & _group)
	:QGraphicsItemGroup(), mGroup(_group)
{
	//Add children
	for(auto & e : mGroup->children())
	{
		QGraphicsItem * new_item(nullptr);

		switch(e->type())
		{
		case AArchElement::Type::Functional:
			new_item = new AGArchFuncElement(static_pointer_cast<AArchFuncElement>(e));
			break;
		case AArchElement::Type::Informational:
			new_item = new AGArchInfoElement(static_pointer_cast<AArchInfoElement>(e));
			break;
		};

		if(new_item)
		{
			addToGroup(new_item);
			new_item->setParentItem(this);
		}
	}

	//Add border
	auto rf = boundingRect();
	m_pBorder = new QGraphicsRectItem(rf, this);
	QPen pen;
	pen.setStyle(Qt::DashLine);
	pen.setWidth(2);
	pen.setBrush(Qt::gray);
	pen.setCapStyle(Qt::RoundCap);
	pen.setJoinStyle(Qt::RoundJoin);
	m_pBorder->setPen(pen);


	setFlag(QGraphicsItem::ItemIsMovable);
	setHandlesChildEvents(false);
}

void AGArchGroup::childGeometryChanged()
{
	auto rf = boundingRect();
	m_pBorder->setRect(rf);
}

#include "AGArchElement.h"
#include <QtWidgets/QGraphicsSceneDragDropEvent>
#include <QtGui/QDrag>
#include <QtWidgets/QWidget>

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
	for(auto & slot : mElement->interface().inputs)
	{
		AGSlotElement * new_slot = new AGSlotElement(slot, this);
		new_slot->setPos(-50, current_height + new_slot->boundingRect().height() / 2);
		current_height += 18;
	}


	setAcceptDrops(true);
	setPos(mElement->pos().x(), mElement->pos().y());
}

void AGArchFuncElement::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	mIsDragging = true;
}

void AGArchFuncElement::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	mIsDragging = false;

	QPointF delta(event->scenePos() - event->buttonDownScenePos(Qt::LeftButton));
	mElement->setPos(mElement->pos() + APoint(delta.x(), delta.y()));
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

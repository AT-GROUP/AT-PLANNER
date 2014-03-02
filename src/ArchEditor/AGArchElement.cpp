
#include "AGArchElement.h"
#include "AGArchLink.h"
#include "AInstanceConfigDialog.h"
#include <ATCore/architecture/AArchElement.h>
#include <ATCore/architecture/AArchElementGroup.h>
#include <ATCore/edfd/DFDElement.h>
#include <QtWidgets/QGraphicsSceneDragDropEvent>
#include <QtGui/QDrag>
#include <QtGui/QPen>
#include <QtWidgets/QWidget>
#include <QtWidgets/QMenu>
#include <QtWidgets/QGraphicsRectItem>
#include <QtWidgets/QInputDialog>
#include <QtCore/QDebug>
#include <QtWidgets/QMessageBox>

using namespace std;

const float START_DRAG_DISTANCE = 10.0f;

AGLinkStarter::AGLinkStarter(QGraphicsItem * parent)
	:QGraphicsRectItem(0, 0, 20, 20, parent)
{
	setBrush(QBrush(QColor(0, 255, 0)));
	setAcceptDrops(true);
}

void AGLinkStarter::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	event->accept();
}


AGArchElement::AGArchElement(const std::shared_ptr<AArchElement> & _element)
	:QGraphicsItemGroup(), mElement(_element)
{
	setCacheMode(QGraphicsItem::CacheMode::NoCache);
	//setHandlesChildEvents(true);
	setFiltersChildEvents(true);
	//setAcceptDrops(true);
	setFlag(QGraphicsItem::ItemIsMovable);

	//Link starter
	m_pLinkStarter = new AGLinkStarter(0);
	m_pLinkStarter->setPos(45, -20);
	addToGroup(m_pLinkStarter);
	m_pLinkStarter->setZValue(20.0);
	//setPos(mElement->pos().x(), mElement->pos().y());

	//Element name
	m_pLabelName = new QGraphicsTextItem(this);
	m_pLabelName->setZValue(50);

	//Element type
	m_pLabelType = new QGraphicsTextItem(this);
	m_pLabelType->setPlainText(QString::fromStdString(element()->interfaceDeclaration().name()));
	m_pLabelType->setPos(- m_pLabelType->boundingRect().width() / 2, - m_pLabelType->boundingRect().height() / 2 + 15);
	m_pLabelType->setZValue(50);

	updateLabel();
}

void AGArchElement::updateLabel()
{
	m_pLabelName->setPlainText(QString::fromStdString(element()->name()));
	m_pLabelName->setPos(- m_pLabelName->boundingRect().width() / 2, - m_pLabelName->boundingRect().height() / 2);
}

AArchElement * AGArchElement::element()
{
	return mElement.get();
}

void AGArchElement::updateElementPos()
{
	auto p = pos();
	mElement->setPos(APoint(p.x(), p.y()));
}

void AGArchElement::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	if(m_pLinkStarter->sceneBoundingRect().contains(event->scenePos()))
	{
		event->ignore();
		emit linkCreatingStarted(this, event->scenePos().toPoint());
	}
	else
	{
		QGraphicsItemGroup::mousePressEvent(event);
	}
}

void AGArchElement::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	updateConnectedLinks();
	QGraphicsItemGroup::mouseMoveEvent(event);
}

void AGArchElement::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	QGraphicsItemGroup::mouseReleaseEvent(event);
	/*mIsDragging = false;
*/
	QPointF delta(event->scenePos() - event->buttonDownScenePos(Qt::LeftButton));
	mElement->setPos(mElement->pos() + APoint(delta.x(), delta.y()));

	setPos(mElement->pos().x(), mElement->pos().y());
	static_cast<AGArchGroup*>(parentItem())->childGeometryChanged();
}

QAction * AGArchElement::showMenuActions(QMenu & menu, const QPoint & pt)
{
	QAction *renameAction = menu.addAction("Rename");
    QAction *deleteAction = menu.addAction("Delete");

	QAction *selectedAction = menu.exec(pt);

	if(selectedAction == renameAction)
	{
		bool ok = false;
		QString new_name = QInputDialog::getText(0, "Rename", "Input new name:", QLineEdit::Normal, QString::fromStdString(element()->name()), &ok);
		if(ok)
		{
			element()->setName(new_name.toStdString());
			updateLabel();
		}

		return nullptr;
	}
	else if(selectedAction == deleteAction)
	{
		int ret = QMessageBox::warning(0, tr("ArchEditor"), tr("Are you sure you want to delete the item?"), QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Cancel);
		if(ret == QMessageBox::Ok)
		{
			emit elementRemovingRequested(this);
		}
		return 0;
	}
	else
		return selectedAction;
}

AGLinkStarter * AGArchElement::linkStarter()
{
	return m_pLinkStarter;
}

void AGArchElement::notifyLinkAboutMoving(AGArchLink * link)
{
	mNotifyableLinks.push_back(link);
}

void AGArchElement::updateConnectedLinks()
{
	for(auto nl : mNotifyableLinks)
		nl->updateShape();
}

void AGArchElement::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QMenu menu;

	showMenuActions(menu, event->screenPos());
}

//==========================AGSlotElement=====================
AGSlotElement::AGSlotElement(const APIKInterface::Slot & _slot, QGraphicsItem * parent)
	:QGraphicsItemGroup(parent), mSlot(_slot)
{
	m_pEllipse = new QGraphicsEllipseItem(0, 0, 16, 16, this);
	m_pEllipse->setBrush(QBrush(QColor(255, 255, 0)));
	m_pEllipse->setPos(-17, -8);

	QGraphicsTextItem * label = new QGraphicsTextItem(QString::fromStdString(mSlot.name), this);
	label->setPos(-16 - label->boundingRect().width() - 3, - label->boundingRect().height() / 2);
}

const std::string & AGSlotElement::slotName() const
{
	return mSlot.name;
}

AArchElement * AGSlotElement::archElement() const
{
	QGraphicsItem * pi = parentItem();
	AGArchElement * par = static_cast<AGArchElement*>(pi);
	return par->element();
}

QGraphicsItem * AGSlotElement::ellipse()
{
	return m_pEllipse;
}

//===================AGArchFuncElement==========================
AGArchFuncElement::AGArchFuncElement(const std::shared_ptr<AArchFuncElement> & _element)
	:AGArchElement(_element)
{
	//Main form

	float rect_height = max(50.0, 18.0 * fElement()->interfaceDeclaration().inputs.size());

	auto rect = new QGraphicsRectItem(-50, -rect_height/2, 100, rect_height, this);
	rect->setBrush(QBrush(QColor(200, 200, 180)));
	rect->setAcceptDrops(true);
	
	
	//Config icon if element has config
	if(fElement()->hasConfig())
	{
		QPixmap config_icon(":/icons/resources/icons/config.png");
		config_icon = config_icon.scaled(24, 24);

		QGraphicsPixmapItem * config_item = new QGraphicsPixmapItem(config_icon, this);
		config_item->setPos(- 50 - config_item->boundingRect().width() / 2, - 25 - config_item->boundingRect().height() / 2);
		config_item->setZValue(100.0);
	}

	//Slots
	float current_height = - rect_height / 2 + 9;
	for(auto & slot : fElement()->interfaceDeclaration().inputs)
	{
		AGSlotElement * new_slot = new AGSlotElement(slot, this);
		new_slot->setPos(-50, current_height + new_slot->boundingRect().height() / 2);
		current_height += 18;

		mSlots[slot.name] = new_slot;
	}

	setPos(fElement()->pos().x(), fElement()->pos().y());
}

AArchFuncElement * AGArchFuncElement::fElement()
{
	return static_cast<AArchFuncElement*>(element());
}

QGraphicsItem * AGArchFuncElement::slotEllipse(const std::string & slot_name)
{
	auto slot_item = mSlots[slot_name];
	return slot_item->ellipse();
}

QAction * AGArchFuncElement::showMenuActions(QMenu & menu, const QPoint & pt)
{
	QAction *config_action = nullptr;
	if(fElement()->hasConfig())
	{
		config_action = menu.addAction("Configuration");
		menu.addSeparator();
	}

	QAction * sel_action = AGArchElement::showMenuActions(menu, pt);
	if(sel_action)
	{
		if(sel_action == config_action)
		{
			AInstanceConfigDialog dlg(fElement()->config());

			if(dlg.exec() == QDialog::Accepted)
			{
				//Update config
				dlg.saveConfig();
			}
			return 0;
		}
	}

	return sel_action;
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

//=======================Info Element==============================
AGArchInfoElement::AGArchInfoElement(const std::shared_ptr<AArchInfoElement> & _element)
	:AGArchElement(_element)
{
	auto rect = new QGraphicsEllipseItem(-50, -25, 100, 50, this);
}

//=========================Group=================================
AGArchGroup::AGArchGroup(const std::shared_ptr<AArchElementGroup> & _group)
	:QGraphicsItemGroup(), mGroup(_group)
{
	//Add children
	for(auto & e : mGroup->children())
	{
		AGArchElement * new_item(nullptr);

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
			//new_item->setParentItem(this);
			new_item->setPos(e->pos().x(), e->pos().y());

			mGElements.push_back(new_item);
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

	//Add label
	m_pLabel = new QGraphicsTextItem(QString::fromStdString(mGroup->dfdElement()->name()), this);
	//m_pLabel->setAcceptDrops(true);


	setPos(_group->pos().x(), _group->pos().y());

	childGeometryChanged();
	setFlag(QGraphicsItem::ItemIsMovable);
	setHandlesChildEvents(false);

	setCacheMode(QGraphicsItem::CacheMode::NoCache);
}

std::shared_ptr<AArchElementGroup> & AGArchGroup::group()
{
	return mGroup;
}

void AGArchGroup::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	QGraphicsItemGroup::mouseReleaseEvent(event);

	for(auto c : childItems())
	{
		auto c_g = qgraphicsitem_cast<AGArchElement*>(c);
		if(c_g)
			c_g->updateElementPos();
	}

	mGroup->setPos(APoint(pos().x(), pos().y()));
}

void AGArchGroup::childGeometryChanged()
{
	auto rf = childrenBoundingRect();
	m_pBorder->setRect(rf);

	//m_pLabel->setPos(rf.left() + m_pLabel->boundingRect().width() / 2, rf.top() + m_pLabel->boundingRect().height() / 2);

	prepareGeometryChange();
}

void AGArchGroup::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	for(auto e : mGElements)
	{
		e->updateConnectedLinks();
	}
	QGraphicsItemGroup::mouseMoveEvent(event);
}
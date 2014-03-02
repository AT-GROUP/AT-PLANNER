
#ifndef AARCHEDITOR_AGArchElement_H
#define AARCHEDITOR_AGArchElement_H

#include <ATCore/architecture/APIKInterface.h>
#include <QtWidgets/QGraphicsItemGroup>
#include <memory>

class AArchElement;
class AArchFuncElement;
class AArchInfoElement;
class AArchElementGroup;
class QMenu;
class QAction;
class AArchLink;
class QGraphicsItem;
class AGArchLink;

class AGLinkStarter : public QGraphicsRectItem
{
public:
	AGLinkStarter(QGraphicsItem * parent = 0);
protected:
	virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

class AGArchElement : public QObject, public QGraphicsItemGroup
{
	Q_OBJECT

public:
	AGArchElement(const std::shared_ptr<AArchElement> & element);
	void updateLabel();
	AArchElement * element();
	void updateElementPos();
	virtual QAction * showMenuActions(QMenu & menu, const QPoint & pt);
	AGLinkStarter * linkStarter();
	void notifyLinkAboutMoving(AGArchLink * link);
	void updateConnectedLinks();
protected:
	virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
	virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

/*	virtual QVariant itemChange(GraphicsItemChange change, const QVariant & value)
	{
		return QGraphicsItemGroup::itemChange(change, value);
	}*/
signals:
	void linkCreatingStarted(AGArchElement * src, QPoint start_point);
	void elementRemovingRequested(AGArchElement * sender);
private:
	std::shared_ptr<AArchElement> mElement;
	AGLinkStarter * m_pLinkStarter;
	std::vector<AGArchLink*> mNotifyableLinks;
	QGraphicsTextItem * m_pLabelName, *m_pLabelType;
};


class AGSlotElement : public QGraphicsItemGroup
{
public:
	AGSlotElement(const APIKInterface::Slot & _slot, QGraphicsItem * parent = 0);
	const std::string & slotName() const;
	AArchElement * archElement() const;
	QGraphicsItem * ellipse();
private:
	APIKInterface::Slot mSlot;
	QGraphicsEllipseItem * m_pEllipse;
};

class AGArchFuncElement : public AGArchElement
{
public:
	AGArchFuncElement(const std::shared_ptr<AArchFuncElement> & element);
	AArchFuncElement * fElement();
	QGraphicsItem * slotEllipse(const std::string & slot_name);
	virtual QAction * showMenuActions(QMenu & menu, const QPoint & pt);
protected:
  /*  void mousePressEvent(QGraphicsSceneMouseEvent *event);
	
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);*/
	
private:
	bool mIsDragging;
	std::map<const std::string, AGSlotElement*> mSlots;
};

class AGArchInfoElement : public AGArchElement
{
public:
	AGArchInfoElement(const std::shared_ptr<AArchInfoElement> & _element);
private:
};

class AGArchGroup : public QGraphicsItemGroup
{
public:
	AGArchGroup(const std::shared_ptr<AArchElementGroup> & group);
	std::shared_ptr<AArchElementGroup> & group();
	void childGeometryChanged();
protected:
	/*
	virtual void prepareGeometryChange()
	{
		QGraphicsItemGroup::prepareGeometryChange();
	}*/
	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
private:
	std::shared_ptr<AArchElementGroup> mGroup;
	std::vector<AGArchElement*> mGElements;
	QGraphicsRectItem * m_pBorder;
	QGraphicsTextItem * m_pLabel;
};

#endif

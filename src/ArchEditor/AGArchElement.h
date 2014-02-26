
#ifndef AARCHEDITOR_AGArchElement_H
#define AARCHEDITOR_AGArchElement_H

#include <QtWidgets/QGraphicsItemGroup>
#include <memory>

class AArchElement;
class AArchFuncElement;
class AArchInfoElement;
class AArchElementGroup;

class AGArchElement : public QGraphicsItemGroup
{
public:
	AGArchElement(const std::shared_ptr<AArchElement> & element);
	AArchElement * element();
	void updateElementPos();
protected:
	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
private:
	std::shared_ptr<AArchElement> mElement;
};

class AGArchFuncElement : public AGArchElement
{
public:
	AGArchFuncElement(const std::shared_ptr<AArchFuncElement> & element);
	AArchFuncElement * fElement();
protected:
  /*  void mousePressEvent(QGraphicsSceneMouseEvent *event);
	
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);*/
	
private:
	
	bool mIsDragging;
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
	void childGeometryChanged();
protected:
	/*virtual QVariant itemChange(GraphicsItemChange change, const QVariant & value)
	{
		return QGraphicsItemGroup::itemChange(change, value);
	}
	virtual void prepareGeometryChange()
	{
		QGraphicsItemGroup::prepareGeometryChange();
	}*/
	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
private:
	std::shared_ptr<AArchElementGroup> mGroup;
	QGraphicsRectItem * m_pBorder;
	QGraphicsTextItem * m_pLabel;
};

#endif

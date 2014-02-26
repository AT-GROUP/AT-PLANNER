
#ifndef AARCHEDITOR_AGArchElement_H
#define AARCHEDITOR_AGArchElement_H

#include <QtWidgets/QGraphicsItemGroup>
#include <memory>

class AArchFuncElement;
class AArchInfoElement;
class AArchElementGroup;

class AGArchFuncElement : public QGraphicsItemGroup
{
public:
	AGArchFuncElement(const std::shared_ptr<AArchFuncElement> & element);
protected:
  /*  void mousePressEvent(QGraphicsSceneMouseEvent *event);
	
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);*/
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
private:
	std::shared_ptr<AArchFuncElement> mElement;
	bool mIsDragging;
};

class AGArchInfoElement : public QGraphicsItemGroup
{
public:
	AGArchInfoElement(const std::shared_ptr<AArchInfoElement> & _element);
private:
	std::shared_ptr<AArchInfoElement> mElement;
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
	
private:
	std::shared_ptr<AArchElementGroup> mGroup;
	QGraphicsRectItem * m_pBorder;
};

#endif

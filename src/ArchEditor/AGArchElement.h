
#ifndef AARCHEDITOR_AGArchElement_H
#define AARCHEDITOR_AGArchElement_H

#include <QtWidgets/QGraphicsItemGroup>
#include <memory>

class AArchFuncElement;
class AArchElementGroup;

class AGArchFuncElement : public QGraphicsItemGroup
{
public:
	AGArchFuncElement(const std::shared_ptr<AArchFuncElement> & element);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
private:
	std::shared_ptr<AArchFuncElement> mElement;
	bool mIsDragging;
};

class AGArchGroup : public QGraphicsItemGroup
{
public:
	AGArchGroup(const std::shared_ptr<AArchElementGroup> & group);
private:
	std::shared_ptr<AArchElementGroup> mGroup;
};

#endif

#ifndef AARCHEDITOR_AGArchElement_H
#define AARCHEDITOR_AGArchElement_H

#include <ATCore/architecture/AArchElement.h>
#include <QtWidgets/QGraphicsItemGroup>
#include <memory>

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

#endif

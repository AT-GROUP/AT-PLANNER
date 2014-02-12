#pragma once
#include <QGraphicsItem>

class DFDGraphicsElement;

class DFDConnection :
	public QGraphicsItem
{
public:

	DFDConnection(DFDGraphicsElement *sourseElement, DFDGraphicsElement *destElement);

	DFDGraphicsElement *sourseElement() const;
	DFDGraphicsElement *destElement() const;

	void adjust();

	void changeText(QString str);

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    DFDGraphicsElement *source, *dest;
	QGraphicsTextItem *text;

    QPointF sourcePoint;
    QPointF destPoint;
    qreal arrowSize;
};


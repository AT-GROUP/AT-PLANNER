#pragma once
#include <QGraphicsItem>
#include <ATCore/edfd/DFDConnection.h>

class DFDGraphicsElement;

class DFDGraphicsConnection : public QGraphicsItem
{
public:
	DFDGraphicsConnection(const std::shared_ptr<DFDConnection> & conn, DFDGraphicsElement *sourseElement, DFDGraphicsElement *destElement);

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

	std::shared_ptr<DFDConnection> m_pConnection;
};


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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
class DFDGraphicsConnection_New : public QGraphicsItemGroup
{
public:
	DFDGraphicsConnection_New(const std::shared_ptr<DFDConnection> & conn, DFDGraphicsElement *sourseElement, DFDGraphicsElement *destElement);

	DFDGraphicsElement *sourseElement() const;
	DFDGraphicsElement *destElement() const;

	//void adjust();
	//void changeText(QString str);

protected:

private:
    DFDGraphicsElement *source, *dest;
	QGraphicsTextItem *text;

    QPointF sourcePoint;
    QPointF destPoint;

	QPointF breakpoint_element_1;
	QPointF breakpoint_element_2;

    qreal arrowSize;

	std::shared_ptr<DFDConnection> m_pConnection;
};
*/

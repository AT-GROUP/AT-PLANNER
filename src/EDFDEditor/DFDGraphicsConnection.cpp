#include <QPainter>
#include <QtCore/qmath.h>
#include "DFDGraphicsConnection.h"
#include "DFDGraphicsElement.h"

static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;

DFDGraphicsConnection::DFDGraphicsConnection(const std::shared_ptr<DFDConnection> & conn, DFDGraphicsElement *sourseElement, DFDGraphicsElement *destElement)
	: m_pConnection(conn), arrowSize(10)
{

	text = new QGraphicsTextItem(this);
	setAcceptedMouseButtons(0);
    source = sourseElement;
    dest = destElement;
    source->addConnection(this);
    dest->addConnection(this);
    adjust();
	text->setPlainText("connection");
}

void DFDGraphicsConnection::changeText(QString str)
{
	text->setPlainText(str);
}

DFDGraphicsElement *DFDGraphicsConnection::sourseElement() const
{
    return source;
}

DFDGraphicsElement *DFDGraphicsConnection::destElement() const
{
    return dest;
}

void DFDGraphicsConnection::adjust()
{
    if (!source || !dest)
        return;

    QLineF line(mapFromItem(source, 50, 20), mapFromItem(dest, 50, 20));
    qreal length = line.length();

    prepareGeometryChange();

    if (length > qreal(20.)) 
	{
		if (qFabs(line.dx()/line.dy()) > 0 && qFabs(line.dx()/line.dy()) < 1)
		{
			if (line.dy() < 0)
			{
				QPointF edgeOffset((line.dx() * 10) / length, (line.dy() * 10) / length);
				QPointF edgeOffsetS(0,-10);
				QPointF edgeOffsetD(0,-10);
				sourcePoint = line.p1() + edgeOffset + edgeOffsetS;
				destPoint = line.p2() - edgeOffset - edgeOffsetD;
			}
			if (line.dy() > 0)
			{
				QPointF edgeOffset((line.dx() * 10) / length, (line.dy() * 10) / length);
				QPointF edgeOffsetS(0,10);
				QPointF edgeOffsetD(0,10);
				sourcePoint = line.p1() + edgeOffset + edgeOffsetS;
				destPoint = line.p2() - edgeOffset - edgeOffsetD;
			}
		}
		else
		{
			if (line.dx() < 0)
			{
				QPointF edgeOffset((line.dx() * 10) / length, (line.dy() * 10) / length);
				QPointF edgeOffsetS(-40,0);
				QPointF edgeOffsetD(-40,0);
				sourcePoint = line.p1() + edgeOffset + edgeOffsetS;
				destPoint = line.p2() - edgeOffset - edgeOffsetD;
			}
			if (line.dx() > 0)
			{
				QPointF edgeOffset((line.dx() * 10) / length, (line.dy() * 10) / length);
				QPointF edgeOffsetS(40,0);
				QPointF edgeOffsetD(40,0);
				sourcePoint = line.p1() + edgeOffset + edgeOffsetS;
				destPoint = line.p2() - edgeOffset - edgeOffsetD;
			}
		}

    } 
	else 
	{
        sourcePoint = destPoint = line.p1();
    }
}

QRectF DFDGraphicsConnection::boundingRect() const
{
    if (!source || !dest)
        return QRectF();

    qreal penWidth = 1;
    qreal extra = (penWidth + arrowSize) / 2.0;

    return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),
                                      destPoint.y() - sourcePoint.y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}

void DFDGraphicsConnection::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (!source || !dest)
        return;

    QLineF line(sourcePoint, destPoint);
    if (qFuzzyCompare(line.length(), qreal(0.)))
        return;

    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(line);

	QPointF pt = line.pointAt(0.5);
	text->setPos(pt.x(),pt.y());

    double angle = ::acos(line.dx() / line.length());
    if (line.dy() >= 0)
        angle = TwoPi - angle;
    QPointF destArrowP1 = destPoint + QPointF(sin(angle - Pi / 3) * arrowSize,
                                              cos(angle - Pi / 3) * arrowSize);
    QPointF destArrowP2 = destPoint + QPointF(sin(angle - Pi + Pi / 3) * arrowSize,
                                              cos(angle - Pi + Pi / 3) * arrowSize);

    painter->setBrush(Qt::black);
    painter->drawPolygon(QPolygonF() << line.p2() << destArrowP1 << destArrowP2);
}

#include <QPainter>
#include <QtCore/qmath.h>
#include <QString>
#include <QtWidgets>
#include "DFDGraphicsConnection.h"
#include "DFDGraphicsElement.h"
#include "AWorkspaceWidget.h"

static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;

DFDGraphicsConnection::DFDGraphicsConnection(const std::shared_ptr<DFDConnection> & conn, DFDGraphicsElement *sourseElement, DFDGraphicsElement *destElement)
	: m_pConnection(conn), arrowSize(10), source(sourseElement), dest(destElement)
{
	setFlag(ItemIsSelectable);
	setFlag(ItemIsFocusable);
	//setFlag(ItemSendsGeometryChanges);
	text_STD = new QGraphicsTextItem(this);
	text_DTS = new QGraphicsTextItem(this);
    source->addConnection(this);
    dest->addConnection(this);
	/*auto line1 = new QGraphicsLineItem(source->x(), source->y(), source->x(), source->y()+10);
	addToGroup(line1);*/
    adjust();
	//text->setPlainText(QString::fromUtf8(conn->name().c_str()));
}

void DFDGraphicsConnection::changeText(QString str)
{
	//text->setPlainText(str);
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
	prepareGeometryChange();
    QLineF line(mapFromItem(source, 50, 20), mapFromItem(dest, 50, 20));
    qreal length = line.length();
	
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

    return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),destPoint.y() - sourcePoint.y())).normalized().adjusted(-extra, -extra, extra, extra);
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
	painter->setBrush(Qt::black);

	QPointF pt = line.pointAt(0.5);
	//text->setPos(pt.x(),pt.y());

	if (m_pConnection->std())
	{
		double angle = ::acos(line.dx() / line.length());
		if (line.dy() >= 0) angle = TwoPi - angle;
		QPointF destArrowP1 = destPoint + QPointF(sin(angle - Pi / 3) * arrowSize, cos(angle - Pi / 3) * arrowSize);
		QPointF destArrowP2 = destPoint + QPointF(sin(angle - Pi + Pi / 3) * arrowSize, cos(angle - Pi + Pi / 3) * arrowSize);
		painter->drawPolygon(QPolygonF() << line.p2() << destArrowP1 << destArrowP2);
	}
	if (m_pConnection->dts())
	{
		double angle = ::acos(line.dx() / line.length());
		if (line.dy() >= 0) angle = TwoPi - angle;
		QPointF sourceArrowP1 = sourcePoint - QPointF(sin(angle - Pi / 3) * arrowSize,cos(angle - Pi / 3) * arrowSize);
		QPointF sourceArrowP2 = sourcePoint - QPointF(sin(angle - Pi + Pi / 3) * arrowSize,cos(angle - Pi + Pi / 3) * arrowSize);
		painter->drawPolygon(QPolygonF() << line.p1() << sourceArrowP1 << sourceArrowP2);
	}


}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
DFDGraphicsConnection_New::DFDGraphicsConnection_New(const std::shared_ptr<DFDConnection> & conn, DFDGraphicsElement *sourseElement, DFDGraphicsElement *destElement)
	: m_pConnection(conn), arrowSize(10)
{
	setFlag(ItemIsSelectable);
	setFlag(ItemIsFocusable);
	//setAcceptedMouseButtons(0);
    source = sourseElement;
    dest = destElement;

	/////////////////////////////////////////////////////////
	text = new QGraphicsTextItem(this);
	text->setPlainText(QString::fromUtf8(conn->name().c_str()));
	////////////////////////////////////////////////////////
}
*/

void DFDGraphicsConnection::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
	QString str;
    menu = new QMenu;

	menuSTD = new QMenu;
	menuSTD->setTitle("Source-To-Dest data");
	menu->addMenu(menuSTD);

	if (!(m_pConnection->std()))
	{
		str = "add data";
		act_slot_1 = new QAction(str,this);
		menuSTD->addAction(act_slot_1);

		connect(act_slot_1, SIGNAL(triggered()), this, SLOT(addSTD()));
	}
	else
	{
		str = "change data";
		act_slot_2 = new QAction(str,this);
		menuSTD->addAction(act_slot_2);
		str = "delete data";
		act_slot_3 = new QAction(str,this);
		menuSTD->addAction(act_slot_3);

		connect(act_slot_2, SIGNAL(triggered()), this, SLOT(changeSTD()));
		connect(act_slot_3, SIGNAL(triggered()), this, SLOT(deleteSTD()));
	}

	menuDTS = new QMenu;
	menuDTS->setTitle("Dest-To-Source data");
	menu->addMenu(menuDTS);

	if (!(m_pConnection->dts()))
	{
		str = "add data";
		act_slot_4 = new QAction(str,this);
		menuDTS->addAction(act_slot_4);

		connect(act_slot_4, SIGNAL(triggered()), this, SLOT(addDTS()));
	}
	else
	{
		str = "change data";
		act_slot_5 = new QAction(str,this);
		menuDTS->addAction(act_slot_5);
		str = "delete data";
		act_slot_6 = new QAction(str,this);
		menuDTS->addAction(act_slot_6);

		connect(act_slot_5, SIGNAL(triggered()), this, SLOT(changeDTS()));
		connect(act_slot_6, SIGNAL(triggered()), this, SLOT(deleteDTS()));
	}

	menu->popup(event->screenPos());
}

//////////////////////////////////////////// SLOTS /////////////////////////////////////////////////////
void DFDGraphicsConnection::addSTD()
{
	QString std_data = QInputDialog::getText(0, "Input source-to-dest data", "Data:", QLineEdit::Normal, QString::fromStdString(m_pConnection->std_d()));
	if (std_data != "")
	{
		m_pConnection->setSTD_data(std_data.toStdString());
		text_STD->setPlainText(QString::fromStdString(m_pConnection->std_d()));
		m_pConnection->setSTD(true);
		text_STD->show();
	}
}

void DFDGraphicsConnection::changeSTD()
{
	QString std_data = QInputDialog::getText(0, "Input source-to-dest data", "Data:", QLineEdit::Normal, QString::fromStdString(m_pConnection->std_d()));
	if ((std_data.toStdString() != m_pConnection->std_d()) && (std_data != ""))
	{
		m_pConnection->setSTD_data(std_data.toStdString());
		text_STD->setPlainText(QString::fromStdString(m_pConnection->std_d()));
	}
}

void DFDGraphicsConnection::deleteSTD()
{
	m_pConnection->setSTD(false);
	text_STD->setPlainText("");
	text_STD->hide();
}

void DFDGraphicsConnection::addDTS()
{
	QString dts_data = QInputDialog::getText(0, "Input dest-to-source data", "Data:", QLineEdit::Normal, QString::fromStdString(m_pConnection->dts_d()));
	if (dts_data != "")
	{
		m_pConnection->setDTS_data(dts_data.toStdString());
		text_DTS->setPlainText(QString::fromStdString(m_pConnection->dts_d()));
		m_pConnection->setDTS(true);
		text_STD->show();
	}
}

void DFDGraphicsConnection::changeDTS()
{
	QString dts_data = QInputDialog::getText(0, "Input dest-to-source data", "Data:", QLineEdit::Normal, QString::fromStdString(m_pConnection->dts_d()));
	if ((dts_data.toStdString() != m_pConnection->dts_d()) && (dts_data != ""))
	{
		m_pConnection->setDTS_data(dts_data.toStdString());
		text_DTS->setPlainText(QString::fromStdString(m_pConnection->dts_d()));
	}
}

void DFDGraphicsConnection::deleteDTS()
{
	m_pConnection->setDTS(false);
	text_DTS->setPlainText("");
	text_DTS->hide();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
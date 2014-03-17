#pragma once
#include <QtWidgets>
#include <QGraphicsItem>
#include <memory>
#include <ATCore/edfd/DFDConnection.h>

class DFDGraphicsElement;

class DFDGraphicsConnection : 
	public QObject, public QGraphicsItemGroup
{
	Q_OBJECT
public:
	
	QMenu *menu;
	QMenu *menuSTD;
	QMenu *menuDTS;

	QAction *act_slot_1;
	QAction *act_slot_2;
	QAction *act_slot_3;
	QAction *act_slot_4;
	QAction *act_slot_5;
	QAction *act_slot_6;

	DFDGraphicsConnection(const std::shared_ptr<DFDConnection> & conn, DFDGraphicsElement *sourseElement, DFDGraphicsElement *destElement);

	DFDGraphicsElement *sourseElement() const;
	DFDGraphicsElement *destElement() const;

	void adjust();

	void changeText(QString str);

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	////////////////////////////////////////////////////////////////
	void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
	//QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    DFDGraphicsElement *source, *dest;
	QGraphicsTextItem *text_STD, *text_DTS;

    QPointF sourcePoint;
    QPointF destPoint;
    qreal arrowSize;

	std::shared_ptr<DFDConnection> m_pConnection;

private slots:
	void addSTD();
	void changeSTD();
	void deleteSTD();
	void addDTS();
	void changeDTS();
	void deleteDTS();
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

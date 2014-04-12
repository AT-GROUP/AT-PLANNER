#pragma once
#include <QtWidgets>
#include <QtWidgets/QGraphicsItem>
#include <memory>
#include <ATCore/edfd/DFDConnection.h>
#include <QtWidgets/QGraphicsRectItem>
#include <QtWidgets/QGraphicsPathItem>
#include "ADatastreamDialog.h"
//#include <boost/signals2.hpp>

class DFDGraphicsElement;

class DFDGraphicsConnection : public QObject, public QGraphicsItemGroup
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
	/*
	void addSTD();
	void changeSTD();
	void deleteSTD();
	void addDTS();
	void changeDTS();
	void deleteDTS();
	*/
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

/*
struct QtRectItem : public QGraphicsRectItem
{
  QtRectItem(QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);

  boost::signals2::signal<void()> m_signal_mouse_move;
  protected:
  void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
};

struct QtPathItem : public QGraphicsItem
{
  QtPathItem(
    const QtRectItem * const from,
    const bool tail,
    const QtRectItem * const mid,
    const bool head,
    const QtRectItem * const to,
    QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);

  ///Respond to key press
  void keyPressEvent(QKeyEvent *event);

  ///Respond to mouse press
  void mousePressEvent(QGraphicsSceneMouseEvent *event);


  protected:
  ///Change the cursor when the user moves the mouse cursor in the bounding rectangle
  void hoverEnterEvent(QGraphicsSceneHoverEvent *event);

  ///The rectangle that containg the item, used for rough calculations like
  ///collision detection
  QRectF boundingRect() const;

  ///Paint a QtPathItem
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

  ///More precise shape compared to boundingRect
  ///In this example, it is redefined to ease selecting those thin lines
  QPainterPath shape() const;

  private:
  ///The extra width given to the line for easier clicking
  static const double m_click_easy_width;

  ///The item where the arrow originates from
  const QtRectItem * const m_from;

  ///Show arrow at head
  bool m_head;

  ///The item where the arrow pass through in the middle
  const QtRectItem * const m_mid;

  ///Show arrow at tail
  bool m_tail;

  ///The item where the arrow points to
  ///(would the arrow and tail heads not be reversible)
  const QtRectItem * const m_to;

  ///Obtain the angle in radians between two deltas
  ///12 o'clock is 0.0 * pi
  /// 3 o'clock is 0.5 * pi
  /// 6 o'clock is 1.0 * pi
  /// 9 o'clock is 1.5 * pi
  //From www.richelbilderbeek.nl/CppGetAngle.htm
  static double GetAngle(const double dx, const double dy);

  ///Obtain point 'beyond'
  QPointF GetBeyond() const;

  ///Obtain point 'center'
  QPointF GetCenter() const;

  ///Obtain the head point of the arrow, on the edge of the rectangle m_from
  QPointF GetHead() const;

  ///Obtain the tail point of the arrow, on the edge of the rectangle m_from
  QPointF GetTail() const;
};*/

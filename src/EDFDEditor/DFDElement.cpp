#include <QtWidgets>
//#include <libxml\tree.h>
//#include <libxml\parser.h>
//#include <vector>
#include "DFDElement.h"
#include "DFDConnection.h"
#include "AWorkspaceWidget.h"


/*void DFDElement::serialize(xmlNode * xml_node) const
{
	//xmlNodeSetContent(xml_node, BAD_CAST "");
}

void DFDElement::deserialize(xmlNodePtr xml_ptrTest2)
{
	
}*/

bool DFDGraphicsElement::CheckConnectingStatus()
{
	if (AAScene->CheckConnectingStatusS() == true) 
		return true;
	else return false;
}

void DFDGraphicsElement::reNa()
{
	QString con_name = QInputDialog::getText(0, "Input new name", "Name:", QLineEdit::Normal, m_pObject->GetName());
	if ((con_name != m_pObject->GetName()) && (con_name != ""))
	{
		m_pObject->SetName(con_name);
		text->setPlainText(m_pObject->GetName());
	}
}

void DFDGraphicsElement::addComm()
{
	QString con_name = QInputDialog::getText(0, "Input connection name", "Name:", QLineEdit::Normal, m_pObject->GetComment());
	m_pObject->SetComment(con_name);
}

void DFDGraphicsElement::conn()
{
	AAScene->SetConnectingStatus(true);
	AAScene->SetActiveItem(this);
}

void DFDGraphicsElement::connTo()
{
	if (AAScene->CheckActiveItem(this) == false)
	{
		DFDConnection *conn = new DFDConnection(AAScene->GetActiveItem(),this);
		QString con_name = QInputDialog::getText(0, "Input connection name", "Name:", QLineEdit::Normal, "");
		conn->changeText(con_name);
		AAScene->AddConnection(conn);
		AAScene->SetConnectingStatus(false);
	}
	else return;
}

void DFDGraphicsElement::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    menu = new QMenu;
	QString str;
	if (CheckConnectingStatus() == false)
	{
		str = "ReName";
		reName = new QAction(str,this);
		reName->setToolTip("Give this object a brand new name!");
		menu->addAction(reName);
		str = "Comment";
		addComment = new QAction(str,this);
		addComment->setToolTip("Smth like mini-specifications");
		menu->addAction(addComment);
		str = "Connect";
		connec = new QAction(str,this);
		connec->setToolTip("Connect me to another object!");
		menu->addAction(connec);
		menu->popup(event->screenPos());
		
		connect(reName, SIGNAL(triggered()), this, SLOT(reNa()));
		connect(addComment, SIGNAL(triggered()), this, SLOT(addComm()));
		connect(connec, SIGNAL(triggered()), this, SLOT(conn()));
	}
	else
	{
		str = "Connect To";
		connectTo = new QAction(str,this);
		connectTo->setToolTip("But wait, there's more!");
		menu->addAction(connectTo);
		menu->popup(event->screenPos());

		connect(connectTo, SIGNAL(triggered()), this, SLOT(connTo()));
	}
}

/////////////////////////////  Connections   /////////////////////////////////

void DFDGraphicsElement::addConnection(DFDConnection *connection)
{
    connectionList << connection;
    connection->adjust();
}

QList<DFDConnection *> DFDGraphicsElement::connections() const
{
    return connectionList;
}

/////////////////////////////      QVariant    /////////////////////////////

QVariant DFDGraphicsEntity::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
    case ItemPositionHasChanged:
		{
			foreach (DFDConnection *connection, connectionList)
            connection->adjust();
			m_pObject->SetPos(this->pos().x(), this->pos().y());
			break;
		}
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
}

QVariant DFDGraphicsFuntion::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
    case ItemPositionHasChanged:
		{
			foreach (DFDConnection *connection, connectionList)
            connection->adjust();
			m_pObject->Mouse_pos = &pos().toPoint();
			break;
		}
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
}

QVariant DFDGraphicsStorage::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
    case ItemPositionHasChanged:
		{
			foreach (DFDConnection *connection, connectionList)
            connection->adjust();
			m_pObject->Mouse_pos = &pos().toPoint();
			break;
		}
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
}

QVariant DFDGraphicsNFFuntion::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
    case ItemPositionHasChanged:
		{
			foreach (DFDConnection *connection, connectionList)
            connection->adjust();
			m_pObject->Mouse_pos = &pos().toPoint();
			break;
		}
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
}

//////////////////////////////////    old code    /////////////////////////////////////////

/*
QRectF DFDGraphicsEntity::boundingRect() const
{
	qreal adjust = 2;
    return QRectF( 0 - adjust, 0 - adjust, 100 + adjust, 40 + adjust);
}

QRectF DFDGraphicsFuntion::boundingRect() const
{
	qreal adjust = 2;
    return QRectF( 0 - adjust, 0 - adjust, 100 + adjust, 40 + adjust);
}

QRectF DFDGraphicsStorage::boundingRect() const
{
	qreal adjust = 2;
    return QRectF( 0 - adjust, 0 - adjust, 100 + adjust, 40 + adjust);
}

QRectF DFDGraphicsNFFuntion::boundingRect() const
{
	qreal adjust = 2;
    return QRectF( 0 - adjust, 0 - adjust, 100 + adjust, 40 + adjust);
}
*/

/*
void DFDGraphicsElement::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	update();
    QGraphicsItemGroup::mousePressEvent(event);
}


void DFDGraphicsElement::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	update();
    QGraphicsItemGroup::mouseReleaseEvent(event);
}
*/

/*QVariant DFDGraphicsElement::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
    case ItemPositionHasChanged:
		{
			break;
		}
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
}*/

/////////////////////////     mouse move event        ////////////////////////

/*
void DFDGraphicsElement::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton))
        .length() < QApplication::startDragDistance()) {
        return;
    }
	QDrag *drag = new QDrag(event->widget());
    QMimeData *mime = new QMimeData;
	mime->setText("123");
    drag->setMimeData(mime);
    drag->exec();
    setCursor(Qt::OpenHandCursor);
}

/*
void DFDGraphicsEntity::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton))
        .length() < QApplication::startDragDistance()) {
        return;
    }
	QDrag *drag = new QDrag(event->widget());
    QMimeData *mime = new QMimeData;
	mime->setText("Entity");
    drag->setMimeData(mime);
    drag->exec();
    setCursor(Qt::OpenHandCursor);
}

/*
void DFDGraphicsFuntion::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton))
        .length() < QApplication::startDragDistance()) {
        return;
    }
	QDrag *drag = new QDrag(event->widget());
    QMimeData *mime = new QMimeData;
	mime->setText("Function");
    drag->setMimeData(mime);
    drag->exec();
    setCursor(Qt::OpenHandCursor);
}

/*
void DFDGraphicsStorage::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton))
        .length() < QApplication::startDragDistance()) {
        return;
    }
	QDrag *drag = new QDrag(event->widget());
    QMimeData *mime = new QMimeData;
	mime->setText("Storage");
    drag->setMimeData(mime);
    drag->exec();
    setCursor(Qt::OpenHandCursor);
}

/*
void DFDGraphicsNFFuntion::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton))
        .length() < QApplication::startDragDistance()) {
        return;
    }
	QDrag *drag = new QDrag(event->widget());
    QMimeData *mime = new QMimeData;
	mime->setText("NFFunction");
    drag->setMimeData(mime);
    drag->exec();
    setCursor(Qt::OpenHandCursor);
}
*/

/*
    QPixmap pixmap(100, 40);
    pixmap.fill(Qt::white);
    QPainter painter(&pixmap);
    painter.translate(15, 15);
    painter.setRenderHint(QPainter::Antialiasing);
    paint(&painter, 0, 0);
    painter.end();
    pixmap.setMask(pixmap.createHeuristicMask());
    drag->setPixmap(pixmap);
    drag->setHotSpot(QPoint(15, 20));
	*/

////////////////////////////////  old code  ////////////////////////////////////////

/*
	ui_CO = new CommentObj();
	ui_CO->SetComment(m_pObject->GetComment());
	ui_CO->exec();
	ui_CO->SetNewComment(m_pObject);
	ui_CO->~CommentObj();
*/

/*
	ui_NO = new NameObj();
	ui_NO->exec();
	ui_NO->SetNewName(m_pObject);
	ui_NO->~NameObj();
*/

////////////////////////////////    MSG Box     ////////////////////////////////////////

/*
	QMessageBox msgBox;
	msgBox.setWindowTitle("My Message Box");
	msgBox.setText("Testing..");
	msgBox.setIcon(QMessageBox::Information);
	msgBox.setInformativeText("Just show infornation.");
	msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
	msgBox.setDefaultButton(QMessageBox::Ok);
	msgBox.exec();
*/

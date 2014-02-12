#include <QtWidgets>
//#include <libxml\tree.h>
//#include <libxml\parser.h>
//#include <vector>
#include "DFDGraphicsElement.h"
#include "DFDGraphicsConnection.h"
#include "AWorkspaceWidget.h"
#include <ATCore/edfd/DFDElement.h>

APoint to_apoint(QPoint q_p)
{
	APoint point;
	point.setX(q_p.x());
	point.setY(q_p.y());

	return point;
}

bool DFDGraphicsElement::CheckConnectingStatus()
{
	if (AAScene->CheckConnectingStatusS() == true) 
		return true;
	else
		return false;
}

void DFDGraphicsElement::reNa()
{
	QString con_name = QInputDialog::getText(0, "Input new name", "Name:", QLineEdit::Normal, QString::fromStdString(m_pObject->name()));
	if ((con_name.toStdString() != m_pObject->name()) && (con_name != ""))
	{
		m_pObject->setName(con_name.toStdString());
		text->setPlainText(QString::fromStdString(m_pObject->name()));
	}
}

void DFDGraphicsElement::addComm()
{
	QString con_name = QInputDialog::getText(0, "Input connection name", "Name:", QLineEdit::Normal, QString::fromStdString(m_pObject->GetComment()));
	m_pObject->SetComment(con_name.toStdString());
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
		/*DFDGraphicsConnection *conn = new DFDGraphicsConnection(AAScene->GetActiveItem(),this);
		QString con_name = QInputDialog::getText(0, "Input connection name", "Name:", QLineEdit::Normal, "");
		conn->changeText(con_name);
		AAScene->AddConnection(conn);
		AAScene->SetConnectingStatus(false);*/
		emit newConnectionRequested(AAScene->GetActiveItem(), this);
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

void DFDGraphicsElement::addConnection(DFDGraphicsConnection *connection)
{
    connectionList << connection;
    connection->adjust();
}

QList<DFDGraphicsConnection *> DFDGraphicsElement::connections() const
{
    return connectionList;
}

QVariant DFDGraphicsElement::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
    case ItemPositionHasChanged:
		{
			foreach (DFDGraphicsConnection *connection, connectionList)
				connection->adjust();
			m_pObject->SetPos(this->pos().x(), this->pos().y());
			break;
		}
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
}
/////////////////////////////      QVariant    /////////////////////////////

DFDGraphicsEntity::DFDGraphicsEntity(const std::shared_ptr<DFDEntity> & ent, AWorkspaceScene *scene)
	:DFDGraphicsElement(ent)
{
	AAScene = scene;
	auto rect = new QGraphicsRectItem(0, 0, 100, 40);
	addToGroup(rect);
	text->setPlainText(QString::fromStdString(ent->name()));
	text->setPos(0,0);
}

DFDGraphicsFuntion::DFDGraphicsFuntion(const std::shared_ptr<DFDFunction> & fun, AWorkspaceScene *scene)
	:DFDGraphicsElement(fun)
{
	AAScene = scene;
	auto elem = new QGraphicsEllipseItem(0, 0, 100, 40); 
	addToGroup(elem);
	text->setPlainText(QString::fromStdString(fun->name()));
	text->setPos(10,10);
}

DFDGraphicsStorage::DFDGraphicsStorage(const std::shared_ptr<DFDStorage> & stor, AWorkspaceScene *scene)
	:DFDGraphicsElement(stor)
{
	AAScene = scene;
	auto rect = new QGraphicsRectItem(0, 0, 20, 40);
	addToGroup(rect);
	rect = new QGraphicsRectItem(20, 0, 80, 40);
	addToGroup(rect);
	text->setPlainText(QString::fromStdString(stor->name()));
	text->setPos(20,0);
}

DFDGraphicsNFFuntion::DFDGraphicsNFFuntion(const std::shared_ptr<DFDNFFunction> & nfun, AWorkspaceScene *scene)
		:DFDGraphicsElement(nfun)
{
	AAScene = scene;
	text->setPlainText(QString::fromStdString(nfun->name()));
	text->setPos(20,20);
}

#include <QtWidgets>
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
		emit newConnectionRequested(AAScene->GetActiveItem(), this);
	}
	else return;
}

void DFDGraphicsElement::setDe()
{
	auto fname = QFileDialog::getOpenFileName(0, "Select file to open", QDir::currentPath(), "EDFD document (*.edfd)");
	if(fname == "")
		return;
	this->m_pObject->mDetalization.used = true;
	this->m_pObject->mDetalization.document_name = fname.toStdString();
}

void DFDGraphicsElement::delDe()
{
	this->m_pObject->mDetalization.used = false;
	this->m_pObject->mDetalization.document_name = "";
}

void DFDGraphicsElement::changeDe()
{
	auto fname = QFileDialog::getOpenFileName(0, "Select file to open", QDir::currentPath(), "EDFD document (*.edfd)");
	if(fname == "")
		return;

	if(fname.toStdString() == this->m_pObject->mDetalization.document_name)
		return;

	this->m_pObject->mDetalization.document_name = fname.toStdString();
}

void DFDGraphicsElement::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    menu = new QMenu;
	QString str;
	if (CheckConnectingStatus() == false)
	{
		str = "Rename";
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
		detMenu = new QMenu;
		detMenu->setTitle("Detalization");
		menu->addMenu(detMenu);
		if (this->m_pObject->mDetalization.used == false)
		{
			str = "Add detalization file";
			setDet = new QAction(str,this);
			setDet->setToolTip("HO-HO-HO");
			detMenu->addAction(setDet);
			connect(setDet, SIGNAL(triggered()), this, SLOT(setDe()));
		}
		else
		{
			str = "Change detalization file";
			chageDet = new QAction(str,this);
			chageDet->setToolTip("HO-HO-HO");
			detMenu->addAction(chageDet);

			str = "Delete detalization";
			delDet = new QAction(str,this);
			delDet->setToolTip("HO-HO-HO");
			detMenu->addAction(delDet);

			connect(delDet, SIGNAL(triggered()), this, SLOT(delDe()));
			connect(chageDet, SIGNAL(triggered()), this, SLOT(changeDe()));
		}

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

//////////////////////////  New Connections  ////////////////////////////
/*
void DFDGraphicsElement::addConnection_new(DFDGraphicsConnection_New *connection)
{
    connectionList_new << connection;
    //connection->adjust();
}

QList<DFDGraphicsConnection_New *> DFDGraphicsElement::connections_new() const
{
    return connectionList_new;
}
*/
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
	auto rect = new QGraphicsRectItem(0, 0, 15, 40);
	addToGroup(rect);

	QPolygonF Triangle1;
	Triangle1.append(QPointF(15,0));
	Triangle1.append(QPointF(100,0));
	QGraphicsPolygonItem *pol1 = new QGraphicsPolygonItem(Triangle1);
	addToGroup(pol1);

	QPolygonF Triangle2;
	Triangle2.append(QPointF(15,40));
	Triangle2.append(QPointF(100,40));
	QGraphicsPolygonItem *pol2 = new QGraphicsPolygonItem(Triangle2);
	addToGroup(pol2);

	text->setPlainText(QString::fromStdString(stor->name()));
	text->setPos(15,0);
}

DFDGraphicsNFFuntion::DFDGraphicsNFFuntion(const std::shared_ptr<DFDNFFunction> & nfun, AWorkspaceScene *scene)
		:DFDGraphicsElement(nfun)
{
	AAScene = scene;

	QPolygonF Triangle1;
	Triangle1.append(QPointF(20,0));
	Triangle1.append(QPointF(0,40));
	Triangle1.append(QPointF(100,40));
	Triangle1.append(QPointF(80,0));
	Triangle1.append(QPointF(20,0));
	QGraphicsPolygonItem *pol1 = new QGraphicsPolygonItem(Triangle1);
	addToGroup(pol1);

	text->setPlainText(QString::fromStdString(nfun->name()));
	text->setPos(15,10);
	
}

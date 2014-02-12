#include <QtWidgets>
#include <QGraphicsEllipseItem>
#include <QMessageBox>
#include "aworkspacewidget.h"
#include "DFDElement.h"
#include "ADrawWidget.h"
#include "DFDConnection.h"
#include <QtWidgets/QInputDialog>

////////////////////////////////  Scene  //////////////////////////////////////

AWorkspaceScene::AWorkspaceScene(QWidget *parent)
    : QGraphicsScene(parent)
{
		connecting = false;
}

bool AWorkspaceScene::CheckConnectingStatusS()
{
	if (connecting == true) 
		return true;
	else return false;
}

void AWorkspaceScene::SetConnectingStatus(bool status)
{
	connecting = status;
}

void AWorkspaceScene::AddConnection(DFDConnection *conn)
{
	this->addItem(conn);
}

bool AWorkspaceScene::CheckActiveItem(DFDGraphicsElement *Act)
{
	if (Th == Act) 
		return true;
	else return false;
}

void AWorkspaceScene::SetActiveItem(DFDGraphicsElement *Act)
{
	Th = Act;
}

DFDGraphicsElement * AWorkspaceScene::GetActiveItem()
{
	return Th;
}

////////////////////////////////////////  Widget  /////////////////////////////////////////////

AWorkspaceWidget::AWorkspaceWidget(QWidget *parent)
    : QGraphicsView(parent)
{
	e = 0;
	f = 0;
    s = 0;
	nf = 0;

	Ascene = new AWorkspaceScene();
	Ascene->setItemIndexMethod(QGraphicsScene::NoIndex);
    setScene(Ascene);
    setAcceptDrops(true);
	QGraphicsRectItem *rect = new QGraphicsRectItem(0,0,3000,3000);
	rect->hide();
	Ascene->addItem(rect);

	/*QString sse = "111";
	QPoint *m_p = new QPoint(-50,-50);
	DFDEntity *ent = new DFDEntity(sse,sse,m_p);
	DFDGraphicsEntity *item1 = new DFDGraphicsEntity(ent, Ascene);
	item1->setPos(m_p->x(),m_p->y());
	Ascene->addItem(item1);

	sse = "222";
	m_p = new QPoint(50,50);
	DFDFunction *fun = new DFDFunction(sse,sse,m_p);
	DFDGraphicsFuntion *item2 = new DFDGraphicsFuntion(fun, Ascene);
	item2->setPos(m_p->x(),m_p->y());
	Ascene->addItem(item2);

	sse = "333";
	m_p = new QPoint(150,150);
	DFDStorage *stor = new DFDStorage(sse,sse,m_p);
	DFDGraphicsStorage *item3 = new DFDGraphicsStorage(stor, Ascene);
	item2->setPos(m_p->x(),m_p->y());
	Ascene->addItem(item3);

	DFDConnection *conn1 = new DFDConnection(item2,item1);
	Ascene->addItem(conn1);*/
	/*DFDConnection *conn2 = new DFDConnection(item2,item3);
	Ascene->addItem(conn2);*/

}


void AWorkspaceWidget::dropEvent(QDropEvent *event)
{

	/////////////////// отладка //////////////////////////
	auto es = event->source();
	auto eso = event->source()->objectName();
	auto esm = event->source()->metaObject();
	auto en = event->mimeData();
	auto e1 = en->parent();
	auto e2 = en->objectName();
	auto e3 = en->urls();
	auto md = event->mimeData()->text();
	//////////////////  отладка  /////////////////////

	QPoint m_p = event->pos();

	if(event->source()->objectName() == "listWidget")               
    {
		if (event->mimeData()->text() == "Test1")
		{
			QString sse;
			sse.setNum(e);
			sse = "entity " + sse;
			DFDEntity *ent = new DFDEntity(sse,sse,&m_p);
			QString con_name = QInputDialog::getText(0, "Input entity name", "Name:", QLineEdit::Normal, ent->GetName());
			ent->SetName(con_name);
			e_M[e] = *ent;
			DFDGraphicsEntity *item = new DFDGraphicsEntity(ent, Ascene);
			item->setPos(e_M[e].Mouse_pos->x(),e_M[e].Mouse_pos->y());
			Ascene->addItem(item);
			e++;
		}
		if (event->mimeData()->text() == "Test2")
		{

			QString sse;
			sse.setNum(f);
			sse = "function " + sse;
			DFDFunction *fun = new DFDFunction(sse,sse,&m_p);
			QString con_name = QInputDialog::getText(0, "Input function name", "Name:", QLineEdit::Normal, fun->GetName());
			fun->SetName(con_name);
			f_M[f] = *fun;
			DFDGraphicsFuntion *item = new DFDGraphicsFuntion(fun, Ascene);
			item->setPos(f_M[f].Mouse_pos->x(),f_M[f].Mouse_pos->y());
			Ascene->addItem(item);
			f++;
		}
		if (event->mimeData()->text() == "Test3")
		{
			QString sse;
			sse.setNum(s);
			sse = "storage " + sse;
			DFDStorage *stor = new DFDStorage(sse,sse,&m_p);
			QString con_name = QInputDialog::getText(0, "Input storage name", "Name:", QLineEdit::Normal, stor->GetName());
			stor->SetName(con_name);
			s_M[s] = *stor;
			DFDGraphicsStorage *item = new DFDGraphicsStorage(stor, Ascene);
			item->setPos(s_M[s].Mouse_pos->x(),s_M[s].Mouse_pos->y());
			Ascene->addItem(item);
			s++;
		}
		if (event->mimeData()->text() == "Test4")
		{
			QString sse;
			sse.setNum(nf);
			sse = "nffunction " + sse;
			DFDNFFunction *nfun = new DFDNFFunction(sse,sse,&m_p);
			QString con_name = QInputDialog::getText(0, "Input nffunction name", "Name:", QLineEdit::Normal, nfun->GetName());
			nfun->SetName(con_name);
			nf_M[nf] = *nfun;
			DFDGraphicsNFFuntion *item = new DFDGraphicsNFFuntion(nfun, Ascene);
			item->setPos(nf_M[nf].Mouse_pos->x(),nf_M[nf].Mouse_pos->y());
			Ascene->addItem(item);
			nf++;
		}
		if (event->mimeData()->text() == "Test5")
		{
			QGraphicsItemGroup *gr = new QGraphicsItemGroup();
			gr->setFlag(QGraphicsItem::ItemIsSelectable,true);
			gr->setFlag(QGraphicsItem::ItemIsMovable,true);
			gr->setFlag(QGraphicsItem::ItemSendsGeometryChanges,true);
			auto rect = new QGraphicsRectItem(0, 0, 150, 60);
			gr->addToGroup(rect);
			gr->setPos(event->pos());
			Ascene->addItem(gr);
			//gr->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
		}
    }
    event->acceptProposedAction();
}

void AWorkspaceWidget::dragEnterEvent(QDragEnterEvent *event)
{
	event->acceptProposedAction();
}

void AWorkspaceWidget::dragMoveEvent(QDragMoveEvent *event)
{
	event->acceptProposedAction();
}



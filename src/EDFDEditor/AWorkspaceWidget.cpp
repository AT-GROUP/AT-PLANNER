#include <QtWidgets>
#include <QGraphicsEllipseItem>
#include <QMessageBox>
#include "aworkspacewidget.h"
#include "DFDGraphicsElement.h"
#include "ADrawWidget.h"
#include "DFDGraphicsConnection.h"
#include <QtWidgets/QInputDialog>

////////////////////////////////  Scene  //////////////////////////////////////

using namespace std;

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

void AWorkspaceScene::AddConnection(DFDGraphicsConnection *conn)
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
/*	e = 0;
	f = 0;
    s = 0;
	nf = 0;*/

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

	DFDGraphicsConnection *conn1 = new DFDGraphicsConnection(item2,item1);
	Ascene->addItem(conn1);*/
	/*DFDGraphicsConnection *conn2 = new DFDGraphicsConnection(item2,item3);
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
	APoint ap(m_p.x(), m_p.y());

	if(event->source()->objectName() == "listWidget")               
    {
		shared_ptr<DFDElement> new_el(nullptr);
		DFDGraphicsElement * new_gr_el(nullptr);

		if (event->mimeData()->text() == "Test1")
		{
			QString sse;
			sse.setNum(4);
			sse = "entity " + sse;
			new_el.reset(new DFDEntity(sse.toStdString(), sse.toStdString(), ap));
			QString con_name = QInputDialog::getText(0, "Input entity name", "Name:", QLineEdit::Normal, QString::fromStdString(new_el->name()));
			new_el->setName(con_name.toStdString());
			
			new_gr_el = new DFDGraphicsEntity(static_pointer_cast<DFDEntity>(new_el), Ascene);
		}
		if (event->mimeData()->text() == "Test2")
		{
			QString sse;
			sse.setNum(5);
			sse = "function " + sse;
			new_el.reset(new DFDFunction(sse.toStdString(), sse.toStdString(),ap));
			QString con_name = QInputDialog::getText(0, "Input function name", "Name:", QLineEdit::Normal, QString::fromStdString(new_el->name()));
			new_el->setName(con_name.toStdString());
			
			new_gr_el = new DFDGraphicsFuntion(static_pointer_cast<DFDFunction>(new_el), Ascene);
		}
		if (event->mimeData()->text() == "Test3")
		{
			QString sse;
			sse.setNum(3);
			sse = "storage " + sse;
			new_el.reset(new DFDStorage(sse.toStdString(), sse.toStdString(), ap));
			QString con_name = QInputDialog::getText(0, "Input storage name", "Name:", QLineEdit::Normal, QString::fromStdString(new_el->name()));
			new_el->setName(con_name.toStdString());

			new_gr_el = new DFDGraphicsStorage(static_pointer_cast<DFDStorage>(new_el), Ascene);

		}
		if (event->mimeData()->text() == "Test4")
		{
			QString sse;
			sse.setNum(6);
			sse = "nffunction " + sse;
			new_el.reset(new DFDNFFunction(sse.toStdString(), sse.toStdString(), ap));
			QString con_name = QInputDialog::getText(0, "Input nffunction name", "Name:", QLineEdit::Normal, QString::fromStdString(new_el->name()));
			new_el->setName(con_name.toStdString());

			new_gr_el = new DFDGraphicsNFFuntion(static_pointer_cast<DFDNFFunction>(new_el), Ascene);
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

		if(new_el)
			m_pDoc->addElement(new_el);

		if(new_gr_el)
		{
			new_gr_el->setPos(new_el->Mouse_pos.x(), new_el->Mouse_pos.y());
			Ascene->addItem(new_gr_el);

			QObject::connect(new_gr_el, &DFDGraphicsElement::newConnectionRequested, this, &AWorkspaceWidget::createConnection);
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

void AWorkspaceWidget::createConnection(DFDGraphicsElement * src, DFDGraphicsElement * dest)
{
	QString con_name = QInputDialog::getText(0, "Input connection name", "Name:", QLineEdit::Normal, "");

	shared_ptr<DFDConnection> conn(new DFDConnection(con_name.toStdString(), src->object(), dest->object()));
	m_pDoc->addConnection(conn);

	DFDGraphicsConnection *gconn = new DFDGraphicsConnection(conn, src, dest);
	Ascene->AddConnection(gconn);
	Ascene->SetConnectingStatus(false);
}

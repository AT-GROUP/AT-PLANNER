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
	Ascene = new AWorkspaceScene();
	Ascene->setItemIndexMethod(QGraphicsScene::NoIndex);
    setScene(Ascene);
    setAcceptDrops(true);
	QGraphicsRectItem *rect = new QGraphicsRectItem(0,0,3000,3000);
	rect->hide();
	Ascene->addItem(rect);
}

template<class ElementClass, class GrClass> DFDGraphicsElement * create_element(const shared_ptr<EDFDDocument> doc, QString ent_name, QString label , shared_ptr<DFDElement> & new_element, const APoint pt, AWorkspaceScene * scene)
{
	QString sse;
	sse.setNum(1);
	sse = ent_name + sse;
	new_element.reset(new ElementClass(sse.toStdString(), sse.toStdString(), pt));
	QString con_name = QInputDialog::getText(0, label, "Name:", QLineEdit::Normal, QString::fromStdString(new_element->name()));
	new_element->setName(con_name.toStdString());
			
	return new GrClass(static_pointer_cast<ElementClass>(new_element), scene);
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
			new_gr_el = create_element<DFDEntity, DFDGraphicsEntity>(m_pDoc, "entity ", "Input entity name", new_el, ap, Ascene);
		}
		if (event->mimeData()->text() == "Test2")
		{
			new_gr_el = create_element<DFDFunction, DFDGraphicsFuntion>(m_pDoc, "function ", "Input function name", new_el, ap, Ascene);
		}
		if (event->mimeData()->text() == "Test3")
		{
			new_gr_el = create_element<DFDStorage, DFDGraphicsStorage>(m_pDoc, "storage ", "Input storage name", new_el, ap, Ascene);

		}
		if (event->mimeData()->text() == "Test4")
		{
			new_gr_el = create_element<DFDNFFunction, DFDGraphicsNFFuntion>(m_pDoc, "nffunction ", "Input nffunction name", new_el, ap, Ascene);
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

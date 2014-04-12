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

void AWorkspaceWidget::deleteIt(QGraphicsItem *elm)
{
	m_pDoc->deleteElement(static_cast<DFDGraphicsElement*>(elm)->m_pObject);
	this->scene()->removeItem(static_cast<DFDGraphicsElement*>(elm));
}

void AWorkspaceWidget::dropEvent(QDropEvent *event)
{
	QPoint m_p = event->pos();
	APoint ap(m_p.x(), m_p.y());

	if(event->source()->objectName() == "listWidget")               
    {
		shared_ptr<DFDElement> new_el(nullptr);
		DFDGraphicsElement * new_gr_el(nullptr);

		if (event->mimeData()->text() == "Entity")
		{
			new_gr_el = create_element<DFDEntity, DFDGraphicsEntity>(m_pDoc, "entity ", "Input entity name", new_el, ap, Ascene);
		}
		if (event->mimeData()->text() == "Function")
		{
			new_gr_el = create_element<DFDFunction, DFDGraphicsFuntion>(m_pDoc, "function ", "Input function name", new_el, ap, Ascene);
		}
		if (event->mimeData()->text() == "Storage")
		{
			new_gr_el = create_element<DFDStorage, DFDGraphicsStorage>(m_pDoc, "storage ", "Input storage name", new_el, ap, Ascene);
		}
		if (event->mimeData()->text() == "NF Function")
		{
			new_gr_el = create_element<DFDNFFunction, DFDGraphicsNFFuntion>(m_pDoc, "nffunction ", "Input nffunction name", new_el, ap, Ascene);
		}
		if (event->mimeData()->text() == "Anchor")
		{
			int it_1 = 0;
			for (auto a : m_pDoc->getElements())
				if (a->type() == DFDElement::Type::Anchor)
				{
					it_1++;
					break;
				}
				if (it_1 == 0)
				{
					new_gr_el = create_element<DFDAnchor, DFDGraphicsAnchor>(m_pDoc, "anchor ", "Input anchor name", new_el, ap, Ascene);
				}
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
	int it_1 = 0;
	for (auto a : m_pDoc->connections())
		if ((a->nameSource() == src->m_pObject && a->nameDest() == dest->m_pObject) || (a->nameSource() == dest->m_pObject && a->nameDest() == src->m_pObject))
		{
			it_1++;
			break;
		}
		if (it_1 == 0)
		{
			QString con_name = QInputDialog::getText(0, "Input connection name", "Name:", QLineEdit::Normal, "");
			shared_ptr<DFDConnection> conn(new DFDConnection(con_name.toStdString(), src->object(), dest->object()));
			m_pDoc->addConnection(conn);
			DFDGraphicsConnection *gconn = new DFDGraphicsConnection(conn, src, dest);
			Ascene->AddConnection(gconn);
			Ascene->SetConnectingStatus(false);
		}
		else
		{
			QMessageBox::information(NULL,QObject::tr("Information"),tr("This objects are already connected"));
		}
}

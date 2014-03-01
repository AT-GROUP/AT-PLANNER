#include "AArchEditor.h"
#include "AGArchElement.h"
#include "AGDocumentView.h"
#include "AGArchLink.h"
#include <ATCore/ACommandExecutor.h>
#include <ATCore/architecture/AArchElement.h>
#include <ATCore/architecture/AArchLink.h>
#include <QtWidgets/QTreeWidgetItem>
#include <QtWidgets/QListWidget>
#include <QtCore/QList>
#include <QtCore/QMimeData>

using namespace std;

APlugin * AT_CREATE_PLUGIN_FN()
{
	return new ArchEditorPlugin();
}


AError ArchEditorPlugin::init(QToolBar * tb, QMenu * menu)
{
	return AError();
}

void ArchEditorPlugin::openFile(ADocument * file)
{
}

const std::string ArchEditorPlugin::documentExtension() const
{
	return "arch";
}

//================Editor===================
//C:\Qt\Qt5.1.1\5.1.1\Src\qttools\src\designer\src\components\widgetbox
SheetDelegate::SheetDelegate(QTreeView *view, QWidget *parent)
    : QItemDelegate(parent),
      m_view(view)
{
}

void SheetDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const QAbstractItemModel *model = index.model();
    Q_ASSERT(model);

    if (!model->parent(index).isValid()) {
        // this is a top-level item.
        QStyleOptionButton buttonOption;

        buttonOption.state = option.state;
#ifdef Q_OS_MAC
        buttonOption.state |= QStyle::State_Raised;
#endif
        buttonOption.state &= ~QStyle::State_HasFocus;

        buttonOption.rect = option.rect;
        buttonOption.palette = option.palette;
        buttonOption.features = QStyleOptionButton::None;

        painter->save();
        QColor buttonColor(230, 230, 230);
        QBrush buttonBrush = option.palette.button();
        if (!buttonBrush.gradient() && buttonBrush.texture().isNull())
            buttonColor = buttonBrush.color();
        QColor outlineColor = buttonColor.darker(150);
        QColor highlightColor = buttonColor.lighter(130);

        // Only draw topline if the previous item is expanded
        QModelIndex previousIndex = model->index(index.row() - 1, index.column());
        bool drawTopline = (index.row() > 0 && m_view->isExpanded(previousIndex));
        int highlightOffset = drawTopline ? 1 : 0;

        QLinearGradient gradient(option.rect.topLeft(), option.rect.bottomLeft());
        gradient.setColorAt(0, buttonColor.lighter(102));
        gradient.setColorAt(1, buttonColor.darker(106));

        painter->setPen(Qt::NoPen);
        painter->setBrush(gradient);
        painter->drawRect(option.rect);
        painter->setPen(highlightColor);
        painter->drawLine(option.rect.topLeft() + QPoint(0, highlightOffset),
                          option.rect.topRight() + QPoint(0, highlightOffset));
        painter->setPen(outlineColor);
        if (drawTopline)
            painter->drawLine(option.rect.topLeft(), option.rect.topRight());
        painter->drawLine(option.rect.bottomLeft(), option.rect.bottomRight());
        painter->restore();

        QStyleOption branchOption;
        static const int i = 9; // ### hardcoded in qcommonstyle.cpp
        QRect r = option.rect;
        branchOption.rect = QRect(r.left() + i/2, r.top() + (r.height() - i)/2, i, i);
        branchOption.palette = option.palette;
        branchOption.state = QStyle::State_Children;

        if (m_view->isExpanded(index))
            branchOption.state |= QStyle::State_Open;

        m_view->style()->drawPrimitive(QStyle::PE_IndicatorBranch, &branchOption, painter, m_view);

        // draw text
        QRect textrect = QRect(r.left() + i*2, r.top(), r.width() - ((5*i)/2), r.height());
        QString text = elidedText(option.fontMetrics, textrect.width(), Qt::ElideMiddle, 
            model->data(index, Qt::DisplayRole).toString());
        m_view->style()->drawItemText(painter, textrect, Qt::AlignCenter,
            option.palette, m_view->isEnabled(), text);

    } else {
        QItemDelegate::paint(painter, option, index);
    }
}

QSize SheetDelegate::sizeHint(const QStyleOptionViewItem &opt, const QModelIndex &index) const
{
    QStyleOptionViewItem option = opt;
    QSize sz = QItemDelegate::sizeHint(opt, index) + QSize(2, 2);
    return sz;
}

AArchEditor::AArchEditor(AGUIEditorPlugin * _plug, QWidget *parent)
	: AGUIEditorInstance(_plug, parent)
{
	ui.setupUi(this);

	ui.treeItems->setItemDelegate(new SheetDelegate(ui.treeItems, ui.treeItems));

	QObject::connect(ui.treeItems, &QTreeWidget::clicked, [=](const QModelIndex & index)
		{
			if(ui.treeItems->isExpanded(index))
				ui.treeItems->collapse(index);
			else
				ui.treeItems->expand(index);
	});

	loadAvalibleElements(command_executor());

	//ui.gvDocument->setScene(new QGraphicsScene());

	connect(ui.gvDocument, &AGDocumentView::itemAdded, [=](AGArchGroup * gr_group, const std::string & PIK_name, const QPoint & position){

		//Get destination group (others)
		auto dest_gr = gr_group->group();
		
		//Get item interface and create new item
		auto new_el = command_executor()->createArchPIKInstance(PIK_name);

		//Add item
		dest_gr->addChild(shared_ptr<AArchElement>(new_el));

		//Reload view
		showDocument();
	});

	connect(ui.gvDocument, &AGDocumentView::linkCreatingFinished, [&](AArchElement * source, AArchElement * dest, const std::string slot_name){
		static_pointer_cast<AArchitectureDocument>(document())->createLink(source, dest, slot_name);
		showDocument();
	});
}

AArchEditor::~AArchEditor()
{

}

class QPIKsListWidget : public QListWidget
{
public:
	QPIKsListWidget(QWidget * parent)
		:QListWidget(parent)
	{

	}
protected:
	virtual QMimeData * mimeData(const QList<QListWidgetItem *> items) const
	{
		if(items.size() > 1)
			return nullptr;

		QListWidgetItem * it = items[0];

		QMimeData * md = new QMimeData();
		md->setText(it->text());
		return md;
	}
};

template<class PIKType> QTreeWidgetItem * create_PIK_categoty(QString category_name, const vector<PIKType> & elements, QTreeWidget * items_widg, QWidget * parent)
{
	QTreeWidgetItem * twi = new QTreeWidgetItem((QTreeWidget*)0, QStringList(category_name));

	QTreeWidgetItem *embed_item = new QTreeWidgetItem(twi);
	embed_item->setFlags(Qt::ItemIsEnabled);
	QListWidget *categoryView = new QPIKsListWidget(parent);
	categoryView->setViewMode(QListView::ListMode);
	items_widg->setItemWidget(embed_item, 0, categoryView);

	categoryView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	categoryView->setSizePolicy(QSizePolicy(QSizePolicy::Ignored, QSizePolicy::Expanding));// categoryView->setMinimumSize(QSize(1111, 1111));
		
	for(auto & pik : elements)
	{
		QListWidgetItem * li = new QListWidgetItem();
		li->setText(QString::fromStdString(pik.name()));
		li->setIcon(QIcon(QPixmap(64, 64)));

		
		categoryView->addItem(li);
	}


	categoryView->setDragEnabled(true);
	categoryView->setDragDropMode(QAbstractItemView::DragOnly);

	return twi;
}

void AArchEditor::loadAvalibleElements(AArchElementFactory * arc_factory)
{
	QList<QTreeWidgetItem *> items;

	items.append(create_PIK_categoty("Document", arc_factory->infPIKs(), ui.treeItems, this));
	items.append(create_PIK_categoty("Functional PIK", arc_factory->funcPIKs(), ui.treeItems, this));

	ui.treeItems->insertTopLevelItems(0, items);
}

void AArchEditor::showDocument()
{
	ui.gvDocument->scene()->clear();

	map<AArchElement*, AGArchElement*> element_index;

	auto doc = static_pointer_cast<AArchitectureDocument>(document());
	for(auto gr : doc->groups())
	{
		AGArchGroup * new_item = new AGArchGroup(gr);
		ui.gvDocument->scene()->addItem(new_item);

		for(auto c : new_item->childItems())
		{
			AGArchElement * el = qgraphicsitem_cast<AGArchElement*>(c);
			if(el)
			{
				connect(el, &AGArchElement::linkCreatingStarted, ui.gvDocument, &AGDocumentView::startLinkDragging);
				element_index[el->element()] = el;
			}
		}
	}

	for(auto link : doc->links())
	{
		AGArchLink * new_link = new AGArchLink(link.get());
		ui.gvDocument->scene()->addItem(new_link);

		AGArchElement * dest_ge = element_index[link->destination()], *src_ge = element_index[link->source()];
		
		new_link->setStartItem(src_ge->linkStarter());
		new_link->setEndItem(static_cast<AGArchFuncElement*>(dest_ge)->slotEllipse(link->slotName()));

		dest_ge->notifyLinkAboutMoving(new_link);
		src_ge->notifyLinkAboutMoving(new_link);

		new_link->updateShape();
	}
}

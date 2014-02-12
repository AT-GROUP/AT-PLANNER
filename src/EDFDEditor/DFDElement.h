#pragma once
#include <QtWidgets>
#include <QGraphicsItem>
#include <QBrush>
//#include <libxml\tree.h>
//#include <libxml\parser.h>
//#include <vector>

class DFDConnection;
class AWorkspaceScene;

/////////////////////// object layer ////////////////////////////////////

class DFDElement
{
public:
	QString mName;
	QString mComment;

	enum class Type {Entity, Storage, Function, NFFunction};
	virtual Type type()=0;

	QPoint *Mouse_pos;

	DFDElement()
	{
		mName = "";
		mComment = "";
	}

	QString GetName()
	{
		return mName;
	}

	void SetName(QString name)
	{
		mName = name;
	}

	QString GetComment()
	{
		return mComment;
	}

	void SetComment(QString comm)
	{
		mComment = comm;
	}

	void SetPos(int x, int y)
	{
		Mouse_pos->setX(x);
		Mouse_pos->setY(y);
	}

	void GetPos()
	{
	}

	//virtual void serialize(xmlNode * xml_node) const;
	//virtual void deserialize(xmlNodePtr xml_ptr);

private:
	std::vector<DFDElement*> mChildren;
};


class DFDEntity : public DFDElement
{
public:
	DFDEntity()
	{
		mName = "";
		mComment = "";
	}

	DFDEntity(QString name, QString comment, QPoint *m_p)
	{
		mName = name;
		mComment = comment;
		Mouse_pos = m_p;
	}

	virtual Type type()
	{
		return Type::Entity;
	}

	/*virtual void serialize(xmlNode * xml_node) const
	{
		DFDElement::serialize(xml_node);
		//сериализация если элемент имеет аттрибуты отличные от DFDElement
	}*/

};


class DFDFunction : public DFDElement
{
public:
	DFDFunction()
	{
		mName = "";
		mComment = "";
	}

	DFDFunction(QString name, QString comment, QPoint *m_p)
	{
		mName = name;
		mComment = comment;
		Mouse_pos = m_p;
	}

	virtual Type type()
	{
		return Type::Function;
	}
};


class DFDStorage : public DFDElement
{
public:
	DFDStorage()
	{
		mName = "";
		mComment = "";
	}

	DFDStorage(QString name, QString comment, QPoint *m_p)
	{
		mName = name;
		mComment = comment;
		Mouse_pos = m_p;
	}

	virtual Type type()
	{
		return Type::Storage;
	}
};


class DFDNFFunction : public DFDElement
{
public:
	DFDNFFunction()
	{
		mName = "";
		mComment = "";
	}

	DFDNFFunction(QString name, QString comment, QPoint *m_p)
	{
		mName = name;
		mComment = comment;
		Mouse_pos = m_p;
	}

	virtual Type type()
	{
		return Type::NFFunction;
	}
};
 
/////////////////// graphics layer //////////////////////////////////////

class DFDGraphicsElement : 
	public QObject, public QGraphicsItemGroup
{
	Q_OBJECT
public:

	QMenu *menu;
	QAction *reName;
	QAction *addComment;
	QAction *connec;
	QAction *connectTo;

	QGraphicsTextItem *text;

    QList<DFDConnection *> connections() const;
	QList<DFDConnection *> connectionList;

    QPointF newPos;
	QPointF *m_pp;

	DFDElement *m_pObject;

	AWorkspaceScene *AAScene;
	
	bool CheckConnectingStatus();

	DFDGraphicsElement(DFDElement *el)
	{
		setFlag(ItemIsSelectable);
		setFlag(ItemIsMovable);
		setFlag(ItemSendsGeometryChanges);
		setCacheMode(DeviceCoordinateCache);
		text = new QGraphicsTextItem(this);
	}

	void addConnection(DFDConnection *connection);

protected:
	void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

private slots:
	void reNa();
	void addComm();
	void conn();
	void connTo();
};


class DFDGraphicsEntity : public DFDGraphicsElement
{
public:

	DFDGraphicsEntity(DFDEntity *ent, AWorkspaceScene *scene)
		:DFDGraphicsElement(ent)
	{
		AAScene = scene;
		m_pObject = ent;
		auto rect = new QGraphicsRectItem(0, 0, 100, 40);
		addToGroup(rect);
		text->setPlainText(ent->GetName());
		text->setPos(0,0);
	}

protected:
	
	QVariant itemChange(GraphicsItemChange change, const QVariant &value);
};


class DFDGraphicsFuntion : public DFDGraphicsElement
{
public:

	DFDGraphicsFuntion(DFDFunction * fun, AWorkspaceScene *scene)
		:DFDGraphicsElement(fun)
	{
		AAScene = scene;
		m_pObject = fun;
		auto elem = new QGraphicsEllipseItem(0, 0, 100, 40); 
		addToGroup(elem);
		text->setPlainText(fun->GetName());
		text->setPos(10,10);
	}

protected:
	
	QVariant itemChange(GraphicsItemChange change, const QVariant &value);
};


class DFDGraphicsStorage : public DFDGraphicsElement
{
public:

	DFDGraphicsStorage(DFDStorage * stor, AWorkspaceScene *scene)
		:DFDGraphicsElement(stor)
	{
		AAScene = scene;
		m_pObject = stor;
		auto rect = new QGraphicsRectItem(0, 0, 20, 40);
		addToGroup(rect);
		rect = new QGraphicsRectItem(20, 0, 80, 40);
		addToGroup(rect);
		text->setPlainText(stor->GetName());
		text->setPos(20,0);
	}

protected:
	
	QVariant itemChange(GraphicsItemChange change, const QVariant &value);
};


class DFDGraphicsNFFuntion : public DFDGraphicsElement
{
public:

	DFDGraphicsNFFuntion(DFDNFFunction * nfun, AWorkspaceScene *scene)
		:DFDGraphicsElement(nfun)
	{
		AAScene = scene;
		m_pObject = nfun;
		text->setPlainText(nfun->GetName());
		text->setPos(20,20);
	}

protected:

	QVariant itemChange(GraphicsItemChange change, const QVariant &value);
};

///////////////////////////////////     old code   ////////////////////////////////

	//void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	//QRectF boundingRect() const;
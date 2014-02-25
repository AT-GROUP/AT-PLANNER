
#ifndef EDFDEditor_DFDGraphicsElement_h
#define EDFDEditor_DFDGraphicsElement_h


#include <QtWidgets>
#include <QGraphicsItem>
#include <QBrush>

#include <memory>

class DFDGraphicsConnection;
class AWorkspaceScene;

class DFDElement;
class DFDEntity;
class DFDFunction;
class DFDStorage;
class DFDNFFunction;

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

	QMenu *detMenu;
	QAction *setDet;
	QAction *delDet;
	QAction *chageDet;

	QGraphicsTextItem *text;

    QList<DFDGraphicsConnection *> connections() const;
	QList<DFDGraphicsConnection *> connectionList;

    QPointF newPos;
	QPointF *m_pp;

	std::shared_ptr<DFDElement> m_pObject;

	AWorkspaceScene *AAScene;
	
	bool CheckConnectingStatus();

	DFDGraphicsElement(const std::shared_ptr<DFDElement> & el)
		:m_pObject(el)
	{
		setFlag(ItemIsSelectable);
		setFlag(ItemIsMovable);
		setFlag(ItemSendsGeometryChanges);
		setCacheMode(DeviceCoordinateCache);
		text = new QGraphicsTextItem(this);
	}

	const std::shared_ptr<DFDElement> & object() const
	{
		return m_pObject;
	}

	void addConnection(DFDGraphicsConnection *connection);

protected:
	void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
	QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private slots:
	void reNa();
	void addComm();
	void conn();
	void connTo();

	void setDe();
	void delDe();
	void changeDe();

signals:
	emit void newConnectionRequested(DFDGraphicsElement * src, DFDGraphicsElement * dest);
};

class DFDGraphicsEntity : public DFDGraphicsElement
{
public:
	DFDGraphicsEntity(const std::shared_ptr<DFDEntity> & ent, AWorkspaceScene *scene);
};

class DFDGraphicsFuntion : public DFDGraphicsElement
{
public:
	DFDGraphicsFuntion(const std::shared_ptr<DFDFunction> & fun, AWorkspaceScene *scene);
};

class DFDGraphicsStorage : public DFDGraphicsElement
{
public:
	DFDGraphicsStorage(const std::shared_ptr<DFDStorage> & stor, AWorkspaceScene *scene);
};

class DFDGraphicsNFFuntion : public DFDGraphicsElement
{
public:
	DFDGraphicsNFFuntion(const std::shared_ptr<DFDNFFunction> & nfun, AWorkspaceScene *scene);
};

#endif

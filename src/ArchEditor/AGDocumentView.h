
#ifndef AARCHEDITOR_AGDocumentView_H
#define AARCHEDITOR_AGDocumentView_H

#include <QtWidgets/QGraphicsView>
#include <QtCore/QString>
#include <QtCore/QPoint>

class AArchScene : public QGraphicsScene
{
public:
	AArchScene();

protected:
	//virtual void dragMoveEvent ( QGraphicsSceneDragDropEvent * event ) override;
};

class AGArchGroup;
class AGArchElement;
class AArchElement;

class AGDocumentView : public QGraphicsView
{
	Q_OBJECT
public:
	AGDocumentView(QWidget *parent = 0);
protected:
    virtual void dragEnterEvent(QDragEnterEvent *event) override;
    virtual void dragMoveEvent(QDragMoveEvent *event) override;
    virtual void dropEvent(QDropEvent *event) override;
	
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);

	virtual void mousePressEvent(QMouseEvent *event);
	
public slots:
	void startLinkDragging(AGArchElement * src, QPoint start_point);
signals:
	void itemAdded(AGArchGroup * group, const std::string & PIK_name, const QPoint & position);
	void linkCreatingFinished(AArchElement * source, AArchElement * dest, const std::string slot_name);
private:
	struct
	{
		bool active;
		QGraphicsLineItem * line;
		QPoint startPoint;
		AGArchElement * source_item;
	} mLinkCreating;

	struct
	{
		bool active;
		QPoint lastPos;
	} mDrag;
};

#endif

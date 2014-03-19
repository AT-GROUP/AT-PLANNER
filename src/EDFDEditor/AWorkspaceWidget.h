#ifndef AWORKSPACEWIDGET_H
#define AWORKSPACEWIDGET_H

#include <QGraphicsView>
#include <QItemSelection>
#include <QTabWidget>
#include "DFDGraphicsElement.h"
#include <ATCore/edfd/DFDElement.h>
#include <ATCore/edfd/EDFDDocument.h>

const int n_M = 100;

class DFDGraphicsConnection;

class AWorkspaceScene : public QGraphicsScene
{
public:
    AWorkspaceScene(QWidget *parent = 0);
	
	bool connecting;
	void SetConnectingStatus(bool status);
	bool CheckConnectingStatusS();

	DFDGraphicsElement *Th;
	void SetActiveItem(DFDGraphicsElement *Act);
	DFDGraphicsElement * GetActiveItem();
	bool CheckActiveItem(DFDGraphicsElement *Act);
	void AddConnection(DFDGraphicsConnection *conn);

protected:
};

class AWorkspaceWidget : public QGraphicsView
{
   Q_OBJECT
public:

    AWorkspaceScene *Ascene;
    AWorkspaceWidget(QWidget *parent = 0);

    void WriteToFile(const QString &fileName);
    void ReadFromFile(const QString &fileName);
	
	void setDocument(const std::shared_ptr<EDFDDocument> & doc)
	{
		m_pDoc = doc;
	}

	void deleteIt(QGraphicsItem *elm);

	virtual void keyPressEvent (QKeyEvent *event)
	{
        switch(event->key())
        {
		case Qt::Key_Delete :
			{
				this->deleteIt(scene()->focusItem());
			}
            break;
        }
	}

public slots:
	void createConnection(DFDGraphicsElement * src, DFDGraphicsElement * dest);
protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);
    //void mousePressEvent(QMouseEvent *event);

private:
	std::shared_ptr<EDFDDocument> m_pDoc;
};

#endif // AWORKSPACEWIDGET_H

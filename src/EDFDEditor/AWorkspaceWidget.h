#ifndef AWORKSPACEWIDGET_H
#define AWORKSPACEWIDGET_H

#include <QGraphicsView>
#include <QItemSelection>
#include <QTabWidget>
#include "DFDElement.h"

const int n_M = 100;

class DFDConnection;

class AWorkspaceScene : public QGraphicsScene
{
   //Q_OBJECT
public:
    AWorkspaceScene(QWidget *parent = 0);
	
	bool connecting;
	void SetConnectingStatus(bool status);
	bool CheckConnectingStatusS();

	DFDGraphicsElement *Th;
	void SetActiveItem(DFDGraphicsElement *Act);
	DFDGraphicsElement * GetActiveItem();
	bool CheckActiveItem(DFDGraphicsElement *Act);
	void AddConnection(DFDConnection *conn);


protected:
    //void dragEnterEvent(QDragEnterEvent *event);
    //void dragMoveEvent(QDragMoveEvent *event);
    //void dropEvent(QDropEvent *event);
    //void mousePressEvent(QMouseEvent *event);
};

class AWorkspaceWidget : public QGraphicsView
{
   Q_OBJECT
public:

	DFDEntity e_M [n_M];
	DFDFunction f_M [n_M];
	DFDStorage s_M [n_M];
	DFDNFFunction nf_M [n_M];

	int e;
	int f;
	int s;
	int nf;

    AWorkspaceScene *Ascene;
    AWorkspaceWidget(QWidget *parent = 0);

    void WriteToFile(const QString &fileName);
    void ReadFromFile(const QString &fileName);

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);
    //void mousePressEvent(QMouseEvent *event);
};

#endif // AWORKSPACEWIDGET_H

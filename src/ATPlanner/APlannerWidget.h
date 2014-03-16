#ifndef APLANNERWIDGET_H
#define APLANNERWIDGET_H

#include "config.h"
#include <QWidget>
#include "ui_APlannerWidget.h"
#include "ATPlanner.h"

class ATPlanner;
class APlan;

class AT_PLANNER_API APlannerWidget : public QWidget
{
	Q_OBJECT

public:
	APlannerWidget(ATPlanner * _planner, QWidget *parent = 0);
	~APlannerWidget();

	/*
	Is called when plan was rebuilt.
	*/
	virtual void planRebuilt(ATPlanner * planner, APlan * plan);

	
	void displayPlan(APlan * new_plan);
signals:
	void startArchDocumentCreated(ADocumentProjectNode * arch_doc_node);
	void projectStructureChanged();

private:
	Ui::APlannerWidget ui;
	ATPlanner * m_pPlanner;
};


#endif // APLANNERWIDGET_H

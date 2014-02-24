#include "APlannerWidget.h"
#include "ATPlanner.h"
#include "ATPlanner.h"
#include "APlan.h"

APlannerWidget::APlannerWidget(ATPlanner * _planner, QWidget *parent)
	: QWidget(parent), m_pPlanner(_planner)
{
	ui.setupUi(this);

	connect(ui.bnRebuilt, &QPushButton::clicked, [=](){m_pPlanner->rebuildPlan();});

	connect(ui.bnBuildCommon, &QPushButton::clicked, [=](){m_pPlanner->buildGeneralizedPlan();});
}

APlannerWidget::~APlannerWidget()
{

}

void APlannerWidget::planRebuilt(ATPlanner * planner, APlan * plan)
{
	displayPlan(plan);
}

void APlannerWidget::displayPlan(APlan * new_plan)
{
	ui.treeCurrentPlan->clear();

	for(auto & t : new_plan->tasks())
	{
		QStringList row;
		row << QString::fromStdString(t->name());
		QTreeWidgetItem * gtask_item = new QTreeWidgetItem(ui.treeCurrentPlan, row);

		ui.treeCurrentPlan->addTopLevelItem(gtask_item);
	}
}

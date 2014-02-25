
#include <ATCore/plan/APlan.h>
#include "APlannerWidget.h"
#include "ATPlanner.h"
#include "ATPlanner.h"

APlannerWidget::APlannerWidget(ATPlanner * _planner, QWidget *parent)
	: QWidget(parent), m_pPlanner(_planner)
{
	ui.setupUi(this);

	
	//Build generalized plan
	connect(ui.bnBuildCommonPlan, &QPushButton::clicked, [=](){m_pPlanner->buildGeneralizedPlan();});

	//Build start architecture model
	connect(ui.bnBuildStartModel, &QPushButton::clicked, [=](){
		auto arch_doc_node = m_pPlanner->buildStartingArchitectureModel();
		emit startArchDocumentCreated(arch_doc_node);
	});
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

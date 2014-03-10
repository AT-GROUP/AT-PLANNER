
#include "APlannerWidget.h"
#include "ATPlanner.h"
#include <ATCore/plan/APlan.h>
#include <ATCore/ACommandExecutor.h>

APlannerWidget::APlannerWidget(ATPlanner * _planner, QWidget *parent)
	: QWidget(parent), m_pPlanner(_planner)
{
	ui.setupUi(this);

	
	//Build generalized plan
	connect(ui.bnBuildCommonPlan, &QPushButton::clicked, [=](){m_pPlanner->buildGeneralizedPlan();});

	//Build start architecture model
	connect(ui.bnBuildStartModel, &QPushButton::clicked, [=](){
		auto arch_doc_node = m_pPlanner->buildStartingArchitectureModel(command_executor());
		emit startArchDocumentCreated(arch_doc_node);
	});

	connect(ui.bnBuildDetailedPlan, &QPushButton::clicked, [=](){
		AError res = m_pPlanner->buildDetailPlan();
		if(!res.OK())
			AError::criticalErrorOccured(res);
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

	
	/*for(auto & t : new_plan->tasks())
	{
		QStringList row;
		row << QString::fromStdString(t->name());
		QTreeWidgetItem * gtask_item = new QTreeWidgetItem(ui.treeCurrentPlan, row);

		ui.treeCurrentPlan->addTopLevelItem(gtask_item);
	}*/

	for(auto & dg : new_plan->displayGroups())
	{
		QStringList row;
		row << QString::fromStdString(dg.general_task->name());
		QTreeWidgetItem * gtask_item = new QTreeWidgetItem(ui.treeCurrentPlan, row);
		ui.treeCurrentPlan->addTopLevelItem(gtask_item);


		for(auto st : dg.sub_tasks)
		{
			QTreeWidgetItem * sub_item = new QTreeWidgetItem(gtask_item);
			sub_item->setText(0, QString::fromStdString(st->name()));
		}
	}
}

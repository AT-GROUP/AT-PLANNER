
#include "APlannerWidget.h"
#include "ATPlanner.h"
#include <ATCore/plan/APlan.h>
#include <ATCore/ACommandExecutor.h>
#include <QtWidgets/QCheckBox>

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

		QString icon_name;

		switch (dg.general_task->dfdType())
		{
		case DFDElement::Type::Function:
			icon_name = "rounded-rectangle.png";
			break;
		case DFDElement::Type::NFFunction:
			icon_name = "trapeze.png";
			break;
		case DFDElement::Type::Storage:
			icon_name = "db.png";
			break;
		default:
			break;
		}
		
		gtask_item->setIcon(0, QIcon(":/ATPlanner/Resources/" + icon_name));

		for(auto st : dg.sub_tasks)
		{
			QTreeWidgetItem * sub_item = new QTreeWidgetItem(gtask_item);
			sub_item->setText(0, QString::fromStdString(st->name()));

			//Checkbox
			QCheckBox * cb = new QCheckBox(ui.treeCurrentPlan);
			cb->setEnabled(false);
			//cb->setCheckable(false);
			cb->setChecked(st->done());
			ui.treeCurrentPlan->setItemWidget(sub_item, 1, cb);

			//Button for executing
			QPushButton * bnExecute = new QPushButton(ui.treeCurrentPlan);
			bnExecute->setText("Execute");
			bnExecute->setEnabled(!st->done());
			connect(bnExecute, &QPushButton::clicked, [=](){
				int res = m_pPlanner->executeTask(st);
				if(!res)
				{
					bnExecute->setEnabled(false);
					//cb->setCheckable(true);
					cb->setChecked(true);
					//cb->setCheckable(false);
				}
			});

			ui.treeCurrentPlan->setItemWidget(sub_item, 2, bnExecute);

		}
	}
}

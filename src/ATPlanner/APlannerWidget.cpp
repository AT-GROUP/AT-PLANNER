#include "APlannerWidget.h"
#include "ATPlanner.h"

APlannerWidget::APlannerWidget(ATPlanner * _planner, QWidget *parent)
	: QWidget(parent), m_pPlanner(_planner)
{
	ui.setupUi(this);

	connect(ui.bnRebuilt, &QPushButton::clicked, [=](){m_pPlanner->rebuildPlan();});
}

APlannerWidget::~APlannerWidget()
{

}

void APlannerWidget::planRebuilt(APlan * plan)
{

}

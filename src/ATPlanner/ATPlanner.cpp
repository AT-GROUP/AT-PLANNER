#include "ATPlanner.h"
#include "APlannerWidget.h"
#include "APlan.h"

ATPlanner::ATPlanner()
	:m_pCurrentPlan(nullptr)
{

}

ATPlanner::~ATPlanner()
{

}

APlannerWidget * ATPlanner::createInfoWidget()
{
	return (m_pPlannerWidget = new APlannerWidget(this));
}

AError ATPlanner::rebuildPlan()
{
	m_pCurrentPlan = new APlan();

	DELEGATE()->planRebuilt(this, m_pCurrentPlan);
	m_pPlannerWidget->planRebuilt(m_pCurrentPlan);
	return AError();
}

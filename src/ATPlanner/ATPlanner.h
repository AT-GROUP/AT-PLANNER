#ifndef ATPlanner_ATPlanner_H
#define ATPlanner_ATPlanner_H

#include "config.h"
#include <ATCore/AError.h>
#include <ATCore/ADelegatedObject.h>

class APlannerWidget;
class ATPlanner;
class APlan;

class AT_PLANNER_API AIPlannerDelegate
{
public:
	virtual void planRebuilt(ATPlanner * planner, APlan * plan) = 0;
};

class AT_PLANNER_API ATPlanner : public ADelegatedObject<AIPlannerDelegate>
{
public:
	ATPlanner();
	~ATPlanner();

	/*
	Creates widget for displaying current plan. ATPlanner also
	will remember it, and call update when plan is rebuilt.
	*/
	APlannerWidget * createInfoWidget();

	AError rebuildPlan();
private:
	APlan * m_pCurrentPlan;
	APlannerWidget * m_pPlannerWidget;
};

#endif // ATPLANNER_H

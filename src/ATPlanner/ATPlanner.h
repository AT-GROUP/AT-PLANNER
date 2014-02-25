#ifndef ATPlanner_ATPlanner_H
#define ATPlanner_ATPlanner_H

#include "config.h"
#include <ATCore/AError.h>
#include <ATCore/ADelegatedObject.h>

class APlannerWidget;
class ATPlanner;
class APlan;
class AProject;
class APluginManager;
class ADocumentProjectNode;

class AT_PLANNER_API APlannerDelegate
{
public:
	virtual void planRebuilt(ATPlanner * planner, APlan * plan) = 0;
};

class AT_PLANNER_API ATPlanner : public ADelegatedObject<APlannerDelegate>
{
public:
	ATPlanner(APluginManager * plugin_mgr);
	~ATPlanner();

	/*
	Creates widget for displaying current plan. ATPlanner also
	will remember it, and call update when plan is rebuilt.
	*/
	APlannerWidget * createInfoWidget();

	AError rebuildPlan();

	void loadProject(AProject * project);

	/*
	Builds generalized plan based on EDFD hierarchy.
	*/
	AError buildGeneralizedPlan();


	/*
	Generates starting architecture model.
	*/
	ADocumentProjectNode * buildStartingArchitectureModel();
private:
	APlan * m_pCurrentPlan;
	APlannerWidget * m_pPlannerWidget;
	AProject * m_pProject;
	APluginManager * m_pPluginManager;
};

#endif // ATPLANNER_H

#include "ATPlanner.h"
#include "APlannerWidget.h"
#include "APlan.h"
#include <ATCore/project/AProject.h>
#include <ATCore/plugin/APluginManager.h>
#include <ATCore/plugin/APlugin.h>

ATPlanner::ATPlanner(APluginManager * plugin_mgr)
	:m_pCurrentPlan(nullptr), m_pPluginManager(plugin_mgr)
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

void ATPlanner::loadProject(AProject * project)
{
	m_pProject = project;
}

AError ATPlanner::buildGeneralizedPlan()
{
	AError err;
	
	//Get preprocessed hierarchy
	auto common_dfd = m_pProject->commonEDFD(&err);

	if(!common_dfd)
		return err;

	//======================================
	//For each link calculate it's sequential cost


	//Find suitable adapter for planner (based on config)
	auto adapters = m_pPluginManager->plugins(APlugin::Type::Adapter);
	if(adapters.size() == 0)
		return AError(AT_ERROR_UNKNOWN, "PDDL adapters not loaded");

	auto adapter = static_cast<AAdapterPlugin*>(adapters[0]->plugin());

	//Solve task with adapter
	adapter->buildGeneralizedPlan(common_dfd.get());

	//Deserialize plan based from adapter result

	return AError();
}

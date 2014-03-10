#include "ATPlanner.h"
#include "APlannerWidget.h"
#include "AStartArchitectureGenerator.h"
#include <ATCore/plan/APlan.h>
#include <ATCore/project/AProject.h>
#include <ATCore/project/AProjectNode.h>
#include <ATCore/plugin/APluginManager.h>
#include <ATCore/plugin/APlugin.h>
#include <ATCore/architecture/AArchitectureDocument.h>
#include <vector>

using namespace std;

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
	m_pPlannerWidget->planRebuilt(this, m_pCurrentPlan);
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
	m_pProject->buildCommonEDFD(&err); ///!!!!!!
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
	APlan * plan = adapter->buildGeneralizedPlan(common_dfd.get());

	//Show plan and make current
	setPlan(plan);

	return AError();
}

ADocumentProjectNode * ATPlanner::buildStartingArchitectureModel(AArchElementFactory * arch_factory)
{
	AError err;
	
	//Get preprocessed hierarchy
	auto common_dfd = m_pProject->commonEDFD(&err);

	if(!common_dfd)
		return nullptr;

	//Create new architecure document
	AArchitectureDocument * arch_doc = new AArchitectureDocument();

	//Build architecure model
	AStartArchitectureGenerator generator;
	generator.generate(arch_factory, common_dfd.get(), arch_doc);

	//Save document to project
	arch_doc->saveToFile(m_pProject->projectDir() + "/main.arch");
	auto doc_node = m_pProject->addDocument(arch_doc);

	//Return saved document
	return doc_node;
}

AError ATPlanner::buildDetailPlan()
{
	AError res;

	//Check that generalized plan is built
	if(!m_pCurrentPlan)
		res = buildGeneralizedPlan();
	if(!res.OK())
		return res;

	//Get architecture document
	vector<const ADocumentProjectNode*> archs;
	m_pProject->documentsWithExtension(archs, "arch");
	if(archs.size() == 0)
		return AError(AT_ERROR_PROJECT_DATA, "Architecture docs not found.");
	else if(archs.size() > 1)
		return AError(AT_ERROR_PROJECT_DATA, "There must be only 1 architecture document.");

	auto doc_path = m_pProject->documentPath(archs[0]);
	shared_ptr<AArchitectureDocument> arch_doc(new AArchitectureDocument());
	arch_doc->loadFromFile(doc_path);

	//Find suitable adapter for planner
	auto adapters = m_pPluginManager->plugins(APlugin::Type::Adapter);
	if(adapters.size() == 0)
		return AError(AT_ERROR_UNKNOWN, "PDDL adapters not loaded");

	auto adapter = static_cast<AAdapterPlugin*>(adapters[0]->plugin());

	//Solve task with adapter, based on generalized plan and architecture
	APlan * new_plan = adapter->buildDetailPlan(m_pCurrentPlan, arch_doc.get());

	//Show plan and make current
	setPlan(new_plan);


	return AError();
}

void ATPlanner::setPlan(APlan * new_plan)
{
	m_pCurrentPlan = new_plan;
	delegate()->planRebuilt(this, new_plan);
}
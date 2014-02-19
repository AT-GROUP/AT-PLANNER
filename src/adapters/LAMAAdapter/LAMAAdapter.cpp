
#include "LAMAAdapter.h"

APlugin * AT_CREATE_PLUGIN_FN()
{
	return new LAMAAdapter();
}

const std::string LAMAAdapter::name()
{
	return "LAMA planner adapter";
}

const std::string LAMAAdapter::description()
{
	return "PDDL adapter for planner LAMA 2011";
}

void LAMAAdapter::buildGeneralizedPlan()
{

}
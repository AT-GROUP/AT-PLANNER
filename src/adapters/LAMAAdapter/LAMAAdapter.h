
#ifndef LAMAAdapter_main_h
#define LAMAAdapter_main_h

#include <ATCore/plugin/APlugin.h>

class APlan;

class AT_PLUGIN_EXPORT LAMAAdapter : public AAdapterPlugin
{
public:
	LAMAAdapter()
		:AAdapterPlugin("LAMA planner adapter", "PDDL adapter for planner LAMA 2011")
	{}

	virtual APlan * buildGeneralizedPlan(const EDFDDocument * common_dfd);
	virtual APlan * buildDetailPlan(APlan * plan, const AArchitectureDocument * arch_doc);
};

#endif
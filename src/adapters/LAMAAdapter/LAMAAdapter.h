
#ifndef LAMAAdapter_main_h
#define LAMAAdapter_main_h

#include <ATCore/plugin/APlugin.h>

class APlan;

class AT_PLUGIN_EXPORT LAMAAdapter : public AAdapterPlugin
{
public:
	virtual const std::string name();
	virtual const std::string description();
	virtual APlan * buildGeneralizedPlan(const EDFDDocument * common_dfd);
};

#endif
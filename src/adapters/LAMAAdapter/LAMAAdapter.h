
#ifndef LAMAAdapter_main_h
#define LAMAAdapter_main_h

#include <ATCore/plugin/APlugin.h>

class AT_PLUGIN_EXPORT LAMAAdapter : public AAdapterPlugin
{
public:
	virtual const std::string name();
	virtual const std::string description();
	virtual void buildGeneralizedPlan(const EDFDDocument * common_dfd);
};

#endif

#ifndef ATVerifier_main_h
#define ATVerifier_main_h

#include <ATCore/plugin/APlugin.h>

class AT_PLUGIN_EXPORT ATVerifierPlugin : public AUtilityPlugin
{
public:
	virtual const std::string name();
	virtual const std::string description();
	virtual const std::vector<std::string> getCommands();
	virtual AError executeCommand(const std::string & script, std::string & answer);
};

#endif

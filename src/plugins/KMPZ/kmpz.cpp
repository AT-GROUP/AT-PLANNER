#include "kmpz.h"

APlugin * AT_CREATE_PLUGIN_FN()
{
	return new ATKMPZPlugin();
}

ATKMPZPlugin::ATKMPZPlugin()
	:AUtilityPlugin("KMPZ", "Combined Method For knowledge Acquisition")
{

}

ATKMPZPlugin::~ATKMPZPlugin()
{

}

const std::vector<std::string> ATKMPZPlugin::getCommands()
{
	std::vector<std::string> res;
	res.push_back("acquire_expert");
	res.push_back("acquire_database");
	return std::move(res);
}

AError ATKMPZPlugin::executeCommand(const std::string & script, std::string & answer)
{
	return AError();
}
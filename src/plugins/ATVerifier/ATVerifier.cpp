
#include "ATVerifier.h"

using namespace std;

APlugin * AT_CREATE_PLUGIN_FN()
{
	return new ATVerifierPlugin();
}

const std::vector<std::string> ATVerifierPlugin::getCommands()
{
	vector<string> result;
	result.push_back("verify");
	return result;
}

AError ATVerifierPlugin::executeCommand(const std::string & script, std::string & answer)
{
	answer = "verified!";
	return AError();
}

#include "ACommandExecutor.h"
#include "plugin/APlugin.h"

AError ACommandExecutor::executeCommand(const std::string & cmd_text, std::string & answer)
{
	AUtilityPlugin * plug = getPluginForCommand(cmd_text);
	if(plug == nullptr)
	{
		answer = "Command not found: '" + cmd_text + "'.";
		return AError(AT_ERROR_COMMAND_NOT_FOUND);
	}
	
	AError res = plug->executeCommand(cmd_text, answer);

	return res;

	
}


AError ACommandExecutor::executeScript(const std::string & script, std::string & answer)
{
	//Now script is only 1 command - must be rewritten to complete parser and analizer

	return executeCommand(script, answer);
}

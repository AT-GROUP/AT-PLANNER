#include "ACommandExecutor.h"
#include "plugin/APlugin.h"

ACommandExecutor::ACommandExecutor()
	:APluginManager()
{
	CommandExecutor::setSingleton(this);
}

AError ACommandExecutor::executeCommand(const std::string & cmd_text, std::string & answer)
{
	error_messenger()->printMessage("Executing command: " + cmd_text);

	AUtilityPlugin * plug = getPluginForCommand(cmd_text);
	if(plug == nullptr)
	{
		answer = "Command not found: '" + cmd_text + "'.";
		return AError(AT_ERROR_COMMAND_NOT_FOUND);
	}
	
	AError res = plug->executeCommand(cmd_text, answer);

	error_messenger()->printMessage("Result: " + answer);
	return res;
}


AError ACommandExecutor::executeScript(const std::string & script, std::string & answer)
{
	//Now script is only 1 command - must be rewritten to complete parser and analizer

	return executeCommand(script, answer);
}


ACommandExecutor * command_executor()
{
	return CommandExecutor::singleton();
}

#ifndef ATCore_APlugin_h
#define ATCore_APlugin_h

#include "../config.h"
#include "../AError.h"
#include <vector>
#include <string>

#define AT_PLUGIN_EXPORT __declspec(dllexport)

#define FUNCTION_NAME(name) #name
#define AT_CREATE_PLUGIN_FN create_plugin_instance
#define AT_CREATE_PLUGIN_FNNAME FUNCTION_NAME(create_plugin_instance)

class AFile;

class AT_CORE_API APlugin
{
public:
	enum class Type {Utility, Editor, Count};

	virtual const std::string name() = 0;
	virtual const std::string description() = 0;
	virtual const Type type() const = 0;
};

extern "C"
{
	AT_PLUGIN_EXPORT APlugin * AT_CREATE_PLUGIN_FN();
}

/*
Utility plugin is invoked when it's command is executed. One utility
plugin can be registered for several commands.
*/
class AT_CORE_API AUtilityPlugin : public APlugin
{
public:
	virtual const Type type() const;
	virtual const std::vector<std::string> getCommands() = 0;
	virtual AError executeCommand(const std::string & script, std::string & answer)=0;
};


/*
Editor plugins are used to create/editing/viewing project files.
*/

class AT_CORE_API AEditorPlugin : public APlugin
{
public:
	virtual const Type type() const;
	virtual void openFile(AFile * file)=0;
	virtual const std::string documentExtension() const = 0;
};


#endif

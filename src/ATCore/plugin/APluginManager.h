

#ifndef ATCore_APluginManager_h
#define ATCore_APluginManager_h

#include "../config.h"
#include "../AError.h"
#include "APlugin.h"
#include <windows.h>
#include <memory>
#include <vector>
#include <map>

typedef APlugin * (*create_plugin_func)();

class AT_CORE_API ADynamicPlugin
{
public:
	ADynamicPlugin(const std::wstring & dll_path);
	~ADynamicPlugin();
	AError load();
	APlugin * plugin() const;
	const wchar_t * path() const;
private:
	std::wstring mLibraryPath;
	HMODULE mDllInstance;
	create_plugin_func mFactoryFunction;
	APlugin * mPluginInstance;
};

class AT_CORE_API APluginManager
{
public:
	virtual ~APluginManager();
	AError loadPlugin(const std::string & plugin_path);
	const std::vector<ADynamicPlugin*> & plugins(APlugin::Type type) const;

	/*
	Creates index for fast command-access.
	*/
	void buildCommandIndex();

	virtual AUtilityPlugin * getPluginForCommand(const std::string & cmd);
protected:
	std::vector<ADynamicPlugin*> mPlugins[APlugin::Type::Count];
	std::map<std::string, AUtilityPlugin*> mCommandIndex;
};

#endif

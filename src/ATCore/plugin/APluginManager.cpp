
#include "APluginManager.h"
#include "APlugin.h"
#include <string>
#include <stdlib.h>

#ifdef AT_OS_WINDOWS
    #include <windows.h>
#elif defined(AT_OS_OSX)
    #include <dlfcn.h>
#endif

using namespace std;

ADynamicPlugin::ADynamicPlugin(const std::wstring & dll_path)
    :mLibraryPath(dll_path), mFactoryFunction(nullptr), mPluginInstance(nullptr), mLibInstance(nullptr)
{
}

AError ADynamicPlugin::load()
{
#ifdef AT_OS_WINDOWS
	mLibInstance = LoadLibrary(mLibraryPath.c_str());

	if(!mLibInstance)
		return AError(AT_ERROR_FILE_NOT_FOUND);
	
	mFactoryFunction = create_plugin_func(GetProcAddress(mLibInstance, AT_CREATE_PLUGIN_FNNAME));

	if(!mFactoryFunction)
	{
		FreeLibrary(mLibInstance);
		return AError(AT_ERROR_INVALID_FILE);
	}

	mPluginInstance = mFactoryFunction();

#elif defined(AT_OS_OSX)
    //.so
    mLibInstance = dlopen((const char*)mLibraryPath.c_str(), RTLD_LAZY);
    if(!mLibInstance)
		return AError(AT_ERROR_FILE_NOT_FOUND);

    mFactoryFunction = (create_plugin_func)dlsym(mLibInstance, AT_CREATE_PLUGIN_FNNAME);

#endif
	return AError();
}


ADynamicPlugin::~ADynamicPlugin()
{
	if(mLibInstance)
	{
#ifdef AT_OS_WINDOWS
        FreeLibrary(mDllInstance);
#elif defined(AT_OS_OSX)
        dlclose(mLibInstance);
#endif
	}
}

APlugin * ADynamicPlugin::plugin() const
{
	return mPluginInstance;
}

const wchar_t * ADynamicPlugin::path() const
{
	return mLibraryPath.c_str();
}

APluginManager::~APluginManager()
{
	for(int i = 0; i < static_cast<int>(APlugin::Type::Count); ++i)
	{
		for(auto plugin : mPlugins[i])
		{
			delete plugin;
		}

		mPlugins[i].clear();
	}
}

AError APluginManager::loadPlugin(const std::string & plugin_path)
{
	wchar_t * buf = new wchar_t[plugin_path.size() ];
	size_t num_chars = mbstowcs(buf, plugin_path.c_str(), plugin_path.size() );
	wstring ws( buf, num_chars );
	delete[] buf;

	ADynamicPlugin * new_plugin = new ADynamicPlugin(ws);
	AError res = new_plugin->load();

	auto plugin_type = new_plugin->plugin()->type();

	mPlugins[static_cast<int>(plugin_type)].push_back(new_plugin);

	return res;
}

const std::vector<ADynamicPlugin*> & APluginManager::plugins(APlugin::Type type) const
{
	return mPlugins[static_cast<int>(type)];
}

void APluginManager::buildCommandIndex()
{
	mCommandIndex.clear();

	for(auto dp : mPlugins[static_cast<int>(APlugin::Type::Utility)])
	{
		auto * plugin(static_cast<AUtilityPlugin*>(dp->plugin()));

		for(auto & cmd : plugin->getCommands())
		{
			auto cmd_it = mCommandIndex.find(cmd);
			if(cmd_it == mCommandIndex.end())
			{
				mCommandIndex.insert(pair<string, AUtilityPlugin*>(cmd, plugin));
			}
			else
				throw AException("Plugin '" + plugin->name() + "' invalid registration, command " + cmd + " already has executor!");
		}
	}
}

AUtilityPlugin * APluginManager::getPluginForCommand(const std::string & cmd)
{
	auto cmd_it = mCommandIndex.find(cmd);
	if(cmd_it == mCommandIndex.end())
		return nullptr;
	else
		return cmd_it->second;
}

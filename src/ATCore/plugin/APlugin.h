
#ifndef ATCore_APlugin_h
#define ATCore_APlugin_h

#include "../config.h"
#include "../AError.h"
#include <vector>
#include <string>
#include <memory>

#define AT_PLUGIN_EXPORT __declspec(dllexport)

#define FUNCTION_NAME(name) #name
#define AT_CREATE_PLUGIN_FN create_plugin_instance
#define AT_CREATE_PLUGIN_FNNAME FUNCTION_NAME(create_plugin_instance)

class ADocument;

class AT_CORE_API APlugin
{
public:
	enum class Type {Utility, Editor, Adapter, Count};

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
Plugin for PDDL-planners integration.
*/
class AT_CORE_API AAdapterPlugin : public APlugin
{
public:
	virtual const Type type() const;
	virtual void buildGeneralizedPlan() = 0;
};

/*
Editor plugins are used to create/editing/viewing project files.
*/

class AEditorInstance;

class AT_CORE_API AEditorPlugin : public APlugin
{
public:
	virtual const Type type() const;
	virtual const std::string documentExtension() const = 0;
	virtual const std::string documentDescription() const = 0;
	virtual const std::string editorTitle() const = 0;
	
	/*
	Creates new document, without any saving.
	*/
	virtual ADocument * createDocument() = 0;

	/*
	Creates document of it's type in given folder. Filename must contain
	extension.
	*/
	ADocument * createFile(const std::string & directory, const std::string & filename);
	virtual ADocument * openFile(const std::string & directory, const std::string & filename);
	virtual void openFile(ADocument * file)=0;

	/*
	Creates editor instance (window).
	*/
	virtual AEditorInstance * createEditorInstance() = 0;
};

class AEditorDelegate
{
public:
	virtual void documentChanged(const std::shared_ptr<ADocument> & doc) = 0;
};

class AT_CORE_API AEditorInstance
{
public:
	AEditorInstance(AEditorPlugin * _plug);
	AEditorPlugin * plugin();

	void openFile(const std::string & file_path);
	void openDocument(const std::shared_ptr<ADocument> & document);
	const std::shared_ptr<ADocument> & document() const;
	void saveCurrentDocument();
	void setDelegate(AEditorDelegate * _delegate);
	virtual void showDocument() = 0;
private:
	AEditorPlugin * m_pPlugin;
	std::shared_ptr<ADocument> m_pDocument;
	AEditorDelegate * m_pDelegate;
};

#endif

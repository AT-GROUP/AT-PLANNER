#include "APlugin.h"
#include "../ADocument.h"

using namespace std;

APlugin::APlugin(Type _type, const std::string & _name, const std::string & _description)
	:m_type(_type), m_name(_name), m_description(_description)
{
}

const std::string & APlugin::name() const
{
	return m_name;
}

const std::string & APlugin::description() const
{
	return m_description;
}

APlugin::Type APlugin::type() const
{
	return m_type;
}

AUtilityPlugin::AUtilityPlugin(const std::string & _name, const std::string & _description)
	:APlugin(APlugin::Type::Utility, _name, _description)
{}

AAdapterPlugin::AAdapterPlugin(const std::string & _name, const std::string & _description)
	: APlugin(APlugin::Type::Adapter, _name, _description)
{}

ADocument * AEditorPlugin::openFile(const std::string & directory, const std::string & filename)
{
	ADocument * new_doc = createDocument();
	new_doc->loadFromFile(directory + "/" + filename);

	return new_doc;
}

AEditorPlugin::AEditorPlugin(const std::string document_extension, const std::string & document_description, const std::string & editor_title, const std::string & _name, const std::string & _description)
	:APlugin(APlugin::Type::Editor, _name, _description), m_docExt(document_extension), m_docDescr(document_description), m_editorTitle(editor_title)
{
}

const std::string & AEditorPlugin::documentExtension() const
{
	return m_docExt;
}

const std::string & AEditorPlugin::documentDescription() const
{
	return m_docDescr;
}

const std::string & AEditorPlugin::editorTitle() const
{
	return m_editorTitle;
}

ADocument * AEditorPlugin::createFile(const std::string & directory, const std::string & filename)
{
	auto * new_doc = createDocument();
	new_doc->saveToFile(directory + "/" + filename);
	return new_doc;
}

AEditorInstance::AEditorInstance(AEditorPlugin * _plug)
	:m_pPlugin(_plug), m_pDocument(nullptr), m_pDelegate(nullptr)
{

}

AEditorPlugin * AEditorInstance::plugin()
{
	return m_pPlugin;
}

void AEditorInstance::openFile(const std::string & file_path)
{
	auto doc = shared_ptr<ADocument>(plugin()->createDocument());
	doc->loadFromFile(file_path);
	openDocument(doc);
}

void AEditorInstance::openDocument(const std::shared_ptr<ADocument> & document)
{
	m_pDocument = document;
	showDocument();
}

const std::shared_ptr<ADocument> & AEditorInstance::document() const
{
	return m_pDocument;
}

void AEditorInstance::saveCurrentDocument()
{
	if(!m_pDocument)
		return;

	m_pDocument->save();
	
	if(m_pDelegate)
		m_pDelegate->documentChanged(m_pDocument);
}

void AEditorInstance::setDelegate(AEditorDelegate * _delegate)
{
	m_pDelegate = _delegate;
}

AEditorDelegate * AEditorInstance::delegate()
{
	return m_pDelegate;
}

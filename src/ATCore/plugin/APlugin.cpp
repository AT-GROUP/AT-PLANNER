#include "APlugin.h"
#include "../ADocument.h"

using namespace std;

const APlugin::Type AUtilityPlugin::type() const
{
	return APlugin::Type::Utility;
}

const APlugin::Type AEditorPlugin::type() const
{
	return APlugin::Type::Editor;
}

ADocument * AEditorPlugin::openFile(const std::string & directory, const std::string & filename)
{
	ADocument * new_doc = createDocument();
	new_doc->loadFromFile(directory + "/" + filename);

	return new_doc;
}

AEditorInstance::AEditorInstance(AEditorPlugin * _plug)
	:m_pPlugin(_plug), m_pDocument(nullptr)
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
}

#include "AArchEditor.h"


APlugin * AT_CREATE_PLUGIN_FN()
{
	return new ArchEditorPlugin();
}


AError ArchEditorPlugin::init(QToolBar * tb, QMenu * menu)
{
	return AError();
}

void ArchEditorPlugin::openFile(AFile * file)
{
}

QWidget * ArchEditorPlugin::createMainWindow()
{
	return new AArchEditor();
}

const std::string ArchEditorPlugin::documentExtension() const
{
	return "arch";
}

//================Editor===================
AArchEditor::AArchEditor(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

AArchEditor::~AArchEditor()
{

}


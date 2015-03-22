#include "AKBEditor.h"

APlugin * AT_CREATE_PLUGIN_FN()
{
	return new KBEditorPlugin();
}

AKBEditor::AKBEditor(AGUIEditorPlugin * _plug, QWidget *parent)
	:AGUIEditorInstance(_plug, parent)
{
	ui.setupUi(this);
}

AKBEditor::~AKBEditor()
{

}

void AKBEditor::showDocument()
{

}

AError KBEditorPlugin::init(QToolBar * tb, QMenu * menu)
{
	return AError();
}

void KBEditorPlugin::openFile(ADocument * file)
{
}

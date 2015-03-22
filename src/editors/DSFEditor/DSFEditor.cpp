#include "DSFEditor.h"

APlugin * AT_CREATE_PLUGIN_FN()
{
	return new DSFEditorPlugin();
}

ADSFEditor::ADSFEditor(AGUIEditorPlugin * _plug, QWidget *parent)
	:AGUIEditorInstance(_plug, parent)
{
	ui.setupUi(this);
}

ADSFEditor::~ADSFEditor()
{
}

void ADSFEditor::showDocument()
{
}

AError DSFEditorPlugin::init(QToolBar * tb, QMenu * menu)
{
	return AError();
}

void DSFEditorPlugin::openFile(ADocument * file)
{
}

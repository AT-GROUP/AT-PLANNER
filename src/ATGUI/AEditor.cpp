#include "AEditor.h"
#include <ATCore/ADocument.h>
/*
AEditor * AAbstractEditorInitializer::init(QToolBar * tb, QMenu * menu)
{
	AEditor * editor = createInstance();
	editor->init(tb, menu);
	return editor;
}

AEditor::AEditor()
	:QWidget()
{

}
*/

AGUIEditorInstance::AGUIEditorInstance(AEditorPlugin * _plug, QWidget * parent)
	:QMainWindow(parent), AEditorInstance(_plug)
{

}

void AGUIEditorInstance::showDocument()
{
	QString new_title(QString::fromStdString(document()->fileName() + " - " + plugin()->editorTitle()));
	setWindowTitle(new_title);
	//emit windowTitleChanged(new_title);
}

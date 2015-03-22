#ifndef AKBEDITOR_H
#define AKBEDITOR_H

#include <QtWidgets/QWidget>
#include <ATGUI/AEditor.h>
#include "ui_AKBEditor.h"
#include "kbeditor_global.h"
#include <ATCore/documents/AKBDocument.h>

class KBEDITOR_EXPORT AKBEditor : public AGUIEditorInstance
{
	Q_OBJECT

public:
	AKBEditor(AGUIEditorPlugin * _plug, QWidget *parent = 0);
	~AKBEditor();
	virtual void showDocument() override;
private:
	Ui::AKBEditor ui;
};

class KBEditorPlugin : public AGUITEditorPlugin<AKBDocument, AKBEditor>
{
	using _Base = AGUITEditorPlugin<AKBDocument, AKBEditor>;
public:
	KBEditorPlugin()
		:_Base("kbs", "Knowldege Base Editor", "Knowldege Base", "Knowledge Base Editor", "Editor for knowledge base / knowledge field in AT representation language.")
	{}

	virtual AError init(QToolBar * tb, QMenu * menu);
	virtual void openFile(ADocument * file);
};


#endif // AKBEDITOR_H

#ifndef DSFEDITOR_H
#define DSFEDITOR_H

#include <ATCore/ADocument.h>
#include <ATGUI/AEditor.h>
#include <QtWidgets/QWidget>
#include "ui_DSFEditor.h"
#include "dsfeditor_global.h"

class DSFDocument : public ADocument
{
public:
	virtual void serialize(_xmlNode * document_node) const override
	{}

	virtual AError deserialize(_xmlNode * document_node) override
	{
		return AError();
	}
};

class DSFEDITOR_EXPORT ADSFEditor : public AGUIEditorInstance
{
	Q_OBJECT

public:
	ADSFEditor(AGUIEditorPlugin * _plug, QWidget *parent = 0);
	~ADSFEditor();
	virtual void showDocument() override;

private:
	Ui::ADSFEditor ui;
};

class DSFEditorPlugin : public AGUITEditorPlugin<DSFDocument, ADSFEditor>
{
	using _Base = AGUITEditorPlugin<DSFDocument, ADSFEditor>;
public:
	DSFEditorPlugin()
		:_Base("dsf", "Dialogue Scenario", "Dialogue Editor", "Dialogue Scenario Editor", "Standard DSF editor.")
	{}

	virtual AError init(QToolBar * tb, QMenu * menu);
	virtual void openFile(ADocument * file);
};


#endif // DSFEDITOR_H

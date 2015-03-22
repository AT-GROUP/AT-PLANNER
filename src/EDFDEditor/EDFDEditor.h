#ifndef EDFDEDITOR_H
#define EDFDEDITOR_H

#include "edfdeditor_global.h"
#include "../EDFDEditor/GeneratedFiles/ui_EDFDEditor.h"

#include <ATGUI/AEditor.h>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGraphicsItemGroup>
#include <QtWidgets/QMainWindow>
#include <memory>

class EDFDDocument;

class AGUIEditorInstance;

class EDFDEDITOR_EXPORT EDFDEditor : public AGUIEditorInstance
{
	Q_OBJECT

public:
	EDFDEditor(AGUIEditorPlugin * _plug, QWidget *parent = 0);
	~EDFDEditor();

	virtual void showDocument() override;

	void updateScene();

public slots:
    void SaveAs();
    void Load();

private:
	Ui::EDFDEditor ui;

	//std::shared_ptr<EDFDDocument> m_pCurrentDocument;
};

class EDFDEditorPlugin : public AGUITEditorPlugin<EDFDDocument, EDFDEditor>
{
	using _Base = AGUITEditorPlugin<EDFDDocument, EDFDEditor>;
public:
	EDFDEditorPlugin()
		:_Base("edfd", "Extended Data Flow Diagramm", "EDFD Editor", "Extended DFD Editor", "Base AT Editor for editing Extended DFD diagrams.")
	{}

	virtual AError init(QToolBar * tb, QMenu * menu);
	virtual void openFile(ADocument * file);
};

#endif // EDFDEDITOR_H

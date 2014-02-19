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
/*
namespace BlockScheme
{
	class AScheme;
	class ABlock;
};

namespace BlockScheme
{
	class AQBlock : public QGraphicsItemGroup
	{
	public:
		AQBlock(BlockScheme::ABlock * block, QGraphicsItem * parent = 0);
	private:
		BlockScheme::ABlock * m_pBlock;
	};
};*/

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
public:
	virtual const std::string name()
	{
		return "Extended DFD Editor";
	}

	virtual const std::string description()
	{
		return "Base AT Editor for editing Extended DFD diagrams.";
	}

	virtual const std::string documentDescription() const
	{
		return "Extended Data Flow Diagramm";
	}

	virtual const std::string editorTitle() const
	{
		return "EDFD Editor";
	}

	virtual const std::string documentExtension() const override;

	virtual AError init(QToolBar * tb, QMenu * menu);
	virtual void openFile(ADocument * file);
	
	virtual ADocument * createFile(const std::string & directory, const std::string & filename) override;

	virtual ADocument * createDocument() override;
};

#endif // EDFDEDITOR_H

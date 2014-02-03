#ifndef EDFDEDITOR_H
#define EDFDEDITOR_H

#include "edfdeditor_global.h"
#include "../EDFDEditor/GeneratedFiles/ui_EDFDEditor.h"

#include <ATGUI/AEditor.h>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGraphicsItemGroup>


class AFile;
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
};

class EDFDEDITOR_EXPORT EDFDEditor : public QWidget
{
	Q_OBJECT

public:
	EDFDEditor(QWidget *parent = 0);
	~EDFDEditor();

	

	void updateScene();
	
private:
	Ui::EDFDEditor ui;

	BlockScheme::AScheme * m_pScheme;
	AFile * m_pFile;
};

class EDFDEditorPlugin : public AGUIEditorPlugin
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

	virtual QWidget * createMainWindow();

	virtual AError init(QToolBar * tb, QMenu * menu);
	virtual void openFile(AFile * file);
	virtual const std::string documentExtension() const override;
};

#endif // EDFDEDITOR_H

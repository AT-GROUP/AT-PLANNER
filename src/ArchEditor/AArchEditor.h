#ifndef AARCHEDITOR_H
#define AARCHEDITOR_H

#include <QtWidgets/QWidget>
#include "ui_AArchEditor.h"
#include <ATGUI/AEditor.h>


class ArchEditorPlugin : public AGUIEditorPlugin
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

class AArchEditor : public QWidget
{
	Q_OBJECT

public:
	AArchEditor(QWidget *parent = 0);
	~AArchEditor();

private:
	Ui::AArchEditor ui;
};

#endif // AARCHEDITOR_H

#ifndef AARCHEDITOR_H
#define AARCHEDITOR_H

#include "ui_AArchEditor.h"
#include <ATCore/architecture/AArchitectureDocument.h>
#include <ATGUI/AEditor.h>
#include <QtWidgets/QWidget>
#include <QtWidgets/QItemDelegate>

class AArchEditor : public AGUIEditorInstance
{
	Q_OBJECT

public:
	AArchEditor(AGUIEditorPlugin * _plug, QWidget *parent = 0);
	~AArchEditor();
	void loadAvalibleElements();
	virtual void showDocument() override;
private:
	Ui::AArchEditor ui;
};


class ArchEditorPlugin : public AGUITEditorPlugin<AArchitectureDocument, AArchEditor>
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
		return "Architecture Model";
	}

	virtual const std::string editorTitle() const
	{
		return "Architecture Model Editor";
	}

	virtual AError init(QToolBar * tb, QMenu * menu);
	virtual void openFile(ADocument * file);

	virtual const std::string documentExtension() const override;
	virtual ADocument * createFile(const std::string & directory, const std::string & filename) override {return 0;};

	virtual ADocument * createDocument() {return 0;}
};


class SheetDelegate: public QItemDelegate
{
    Q_OBJECT
public:
    SheetDelegate(QTreeView *view, QWidget *parent);

    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    virtual QSize sizeHint(const QStyleOptionViewItem &opt, const QModelIndex &index) const;

private:
    QTreeView *m_view;
};

#endif // AARCHEDITOR_H

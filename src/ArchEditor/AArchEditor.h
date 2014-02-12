#ifndef AARCHEDITOR_H
#define AARCHEDITOR_H

#include "ui_AArchEditor.h"
#include <ATGUI/AEditor.h>
#include <QtWidgets/QWidget>
#include <QtWidgets/QItemDelegate>

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

class AArchEditor : public QWidget
{
	Q_OBJECT

public:
	AArchEditor(QWidget *parent = 0);
	~AArchEditor();
	void loadAvalibleElements();
private:
	Ui::AArchEditor ui;
};

#endif // AARCHEDITOR_H

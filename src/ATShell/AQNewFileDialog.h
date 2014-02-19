#ifndef AQNEWFILEDIALOG_H
#define AQNEWFILEDIALOG_H

#include <QDialog>
#include "ui_AQNewFileDialog.h"
#include <vector>

class APluginManager;
class AEditorPlugin;

class AQNewFileDialog : public QDialog
{
	Q_OBJECT

public:
	AQNewFileDialog(APluginManager * pmgr, QWidget *parent = 0);
	~AQNewFileDialog();
	QString fileName();
	AEditorPlugin * selectedTypeEditor() const;
private:
	Ui::AQNewFileDialog ui;
	std::vector<AEditorPlugin*> mEditors;
	AEditorPlugin * mSelectedTypeEditor;
};

#endif // AQNEWFILEDIALOG_H

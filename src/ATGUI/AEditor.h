#ifndef AEDITOR_H
#define AEDITOR_H

#include "config.h"
#include <ATCore/AError.h>
#include <ATCore/plugin/APlugin.h>
#include <QtWidgets/QWidget>
#include <QtWidgets/QToolbar>
#include <QtWidgets/QMenu>

//class AEditor;

/*
Creates editor instance for further usage in AT environment.
*/
/*class AT_GUI_API AAbstractEditorInitializer
{
public:
	//Initializes and returns central widget
	AEditor * init(QToolBar * tb, QMenu * menu);
private:
	virtual AEditor * createInstance()=0;
};

template<class T>
class AEditorInitializer : public AAbstractEditorInitializer
{
	virtual AEditor * createInstance()
	{
		return new T();
	}
};
*/

class AT_GUI_API AGUIEditorPlugin : public QWidget, public AEditorPlugin
{
//	Q_OBJECT

public:
	//AEditor();
	virtual AError init(QToolBar * tb, QMenu * menu)=0;
	virtual QWidget * createMainWindow() = 0;
};
/*
extern "C"
{
__declspec(dllexport) AEditor * create_editor_instance();
}
*/
#endif

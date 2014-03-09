#ifndef AEDITOR_H
#define AEDITOR_H

#include "config.h"
#include <ATCore/AError.h>
#include <ATCore/plugin/APlugin.h>
#include <QtWidgets/QWidget>
#include <QtWidgets/QToolbar>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMainWindow>

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

class AGUIEditorInstance;

class AT_GUI_API AGUIEditorPlugin : public AEditorPlugin
{
//	Q_OBJECT

public:
	//AEditor();
	virtual AError init(QToolBar * tb, QMenu * menu)=0;
};

template<class DocType, class EdInstType> class AGUITEditorPlugin : public AGUIEditorPlugin
{
public:
	virtual EdInstType * createEditorInstance()
	{
		return new EdInstType(this, 0);
	}

	virtual DocType * createDocument()
	{
		return new DocType();
	}

/*	virtual std::shared_ptr<DocType> document() override
	{
		return static_pointer_cast<DocType>(AGUIEditorPlugin::document());
	}*/
};

//AT_GUI_API
class Q_DECL_EXPORT AGUIEditorInstance : public QMainWindow, public AEditorInstance
{
public:
	AGUIEditorInstance(AEditorPlugin * _plug, QWidget * parent);
	virtual void showDocument() override;
	void requestDocumentOpen(const std::string & document_name);
public slots:
	void saveFileInitiated();
private:
};

//AT_GUI_API const QMetaObject AGUIEditorInstance::staticMetaObject;

/*
extern "C"
{
__declspec(dllexport) AEditor * create_editor_instance();
}
*/
#endif

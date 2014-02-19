#include "EDFDEditor.h"

#include <ATCore/edfd/AScheme.h>
#include <ATCore/plugin/APlugin.h>
#include <ATCore/edfd/EDFDDocument.h>

#include <QtWidgets/QFileDialog.h>

//using namespace BlockScheme;
using namespace std;

APlugin * AT_CREATE_PLUGIN_FN()
{
	return new EDFDEditorPlugin();
}
/*
AQBlock::AQBlock(BlockScheme::ABlock * _block, QGraphicsItem * parent)
	:QGraphicsItemGroup(parent), m_pBlock(_block)
{

}*/

EDFDEditor::EDFDEditor(AGUIEditorPlugin * _plug, QWidget *parent)
	: AGUIEditorInstance(_plug, parent)
{
	ui.setupUi(this);

//	QGraphicsScene * scene = new QGraphicsScene();
//	ui.graphicsView->setScene(scene);


    connect(ui.ANewFile, SIGNAL(triggered()), this, SLOT(NewFile()));
    connect(ui.ASave, &QAction::triggered, [=]()
		{
			saveCurrentDocument();
	});

    connect(ui.ASaveAs, SIGNAL(triggered()), this, SLOT(SaveAs()));
    connect(ui.ALoad, SIGNAL(triggered()), this, SLOT(Load()));
    connect(ui.AExit, SIGNAL(triggered()), this, SLOT(close()));
}

EDFDEditor::~EDFDEditor()
{

}

void EDFDEditor::showDocument()
{
	AGUIEditorInstance::showDocument();

	ui.gvDocument->setDocument(static_pointer_cast<EDFDDocument>(document()));
	updateScene();
}

void EDFDEditor::updateScene()
{
	ui.gvDocument->scene()->clear();

/*	for(auto i : m_pScheme->mBlocks)
	{
		AQBlock * block = new AQBlock(i);
		ui.graphicsView->scene()->addItem(block);
	}*/
}

void EDFDEditor::SaveAs()
{
    //create new file and save to it
	auto fname = QFileDialog::getSaveFileName(0, "Select file to save", QDir::currentPath(), "EDFD document (*.edfd)");
	if(fname != "")
	{
		document()->saveToFile(fname.toStdString());
	}
}

void EDFDEditor::Load()
{
	//Load existing file

	auto fname = QFileDialog::getOpenFileName(0, "Select file to open", QDir::currentPath(), "EDFD document (*.edfd)");
	if(fname == "")
		return;

	/*shared_ptr<EDFDDocument> new_doc(new EDFDDocument());
	auto res = new_doc->loadFromFile(fname.toStdString());

	if(res.OK())
	{
		m_pCurrentDocument = new_doc;
		
	}*/
	
	openFile(fname.toStdString());
}

AError EDFDEditorPlugin::init(QToolBar * tb, QMenu * menu)
{
	return AError();
}

void EDFDEditorPlugin::openFile(ADocument * file)
{
	//Load scheme from file
//	AScheme * new_scheme = new AScheme();

	/*m_pFile = file;
	m_pScheme = new_scheme;

	updateScene();*/
}

const std::string EDFDEditorPlugin::documentExtension() const
{
	return "edfd";
}

ADocument * EDFDEditorPlugin::createFile(const std::string & directory, const std::string & filename)
{
	EDFDDocument * new_doc = new EDFDDocument();
	new_doc->saveToFile(directory + "/" + filename);
	return new_doc;
}

ADocument * EDFDEditorPlugin::createDocument()
{
	return new EDFDDocument();
}

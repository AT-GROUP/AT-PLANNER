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

EDFDEditor::EDFDEditor(QWidget *parent)
	: QMainWindow(parent), m_pCurrentDocument(nullptr)
{
	ui.setupUi(this);

//	QGraphicsScene * scene = new QGraphicsScene();
//	ui.graphicsView->setScene(scene);


    connect(ui.ANewFile, SIGNAL(triggered()), this, SLOT(NewFile()));
    connect(ui.ASave, SIGNAL(triggered()), this, SLOT(Save()));
    connect(ui.ASaveAs, SIGNAL(triggered()), this, SLOT(SaveAs()));
    connect(ui.ALoad, SIGNAL(triggered()), this, SLOT(Load()));
    connect(ui.AExit, SIGNAL(triggered()), this, SLOT(close()));

	newFile();
}

EDFDEditor::~EDFDEditor()
{

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

void EDFDEditor::newFile()
{
    //Create new file
	m_pCurrentDocument = shared_ptr<EDFDDocument>(new EDFDDocument());
	ui.gvDocument->setDocument(m_pCurrentDocument);
	updateScene();
}

void EDFDEditor::SaveAs()
{
    //create new file and save to it
	auto fname = QFileDialog::getSaveFileName(0, "Select file to save", QDir::currentPath(), "EDFD document (*.edfd)");
	if(fname != "")
	{
		m_pCurrentDocument->saveToFile(fname.toStdString());
		ui.gvDocument->setDocument(m_pCurrentDocument);
	}
}

void EDFDEditor::Save()
{
    //rewrite existing file
}

void EDFDEditor::Load()
{
	//Load existing file

	auto fname = QFileDialog::getOpenFileName(0, "Select file to open", QDir::currentPath(), "EDFD document (*.edfd)");
	if(fname == "")
		return;

	shared_ptr<EDFDDocument> new_doc(new EDFDDocument());
	auto res = new_doc->loadFromFile(fname.toStdString());

	if(res.OK())
	{
		m_pCurrentDocument = new_doc;
		updateScene();
	}
	
}

AError EDFDEditorPlugin::init(QToolBar * tb, QMenu * menu)
{
	return AError();
}

void EDFDEditorPlugin::openFile(AFile * file)
{
	//Load scheme from file
//	AScheme * new_scheme = new AScheme();

	/*m_pFile = file;
	m_pScheme = new_scheme;

	updateScene();*/
}

QWidget * EDFDEditorPlugin::createMainWindow()
{
	return new EDFDEditor();
}

const std::string EDFDEditorPlugin::documentExtension() const
{
	return "edfd";
}


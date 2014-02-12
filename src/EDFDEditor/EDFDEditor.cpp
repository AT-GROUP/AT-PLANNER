#include "EDFDEditor.h"

#include <ATCore/edfd/AScheme.h>
#include <ATCore/plugin/APlugin.h>

using namespace BlockScheme;

APlugin * AT_CREATE_PLUGIN_FN()
{
	return new EDFDEditorPlugin();
}

AQBlock::AQBlock(BlockScheme::ABlock * _block, QGraphicsItem * parent)
	:QGraphicsItemGroup(parent), m_pBlock(_block)
{

}

EDFDEditor::EDFDEditor(QWidget *parent)
	: QWidget(parent), m_pScheme(0), m_pFile(0)
{
	ui.setupUi(this);

	QGraphicsScene * scene = new QGraphicsScene();
	ui.graphicsView->setScene(scene);
}

EDFDEditor::~EDFDEditor()
{

}

void EDFDEditor::updateScene()
{
	ui.graphicsView->scene()->clear();

	for(auto i : m_pScheme->mBlocks)
	{
		AQBlock * block = new AQBlock(i);
		ui.graphicsView->scene()->addItem(block);
	}
}

AError EDFDEditorPlugin::init(QToolBar * tb, QMenu * menu)
{
	return AError();
}

void EDFDEditorPlugin::openFile(AFile * file)
{
	//Load scheme from file
	AScheme * new_scheme = new AScheme();

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

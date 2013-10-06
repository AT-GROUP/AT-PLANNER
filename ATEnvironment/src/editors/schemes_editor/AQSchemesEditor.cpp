#include "AQSchemesEditor.h"
#include "../../scheme/AScheme.h"

using namespace BlockScheme;

AQBlock::AQBlock(BlockScheme::ABlock * _block, QGraphicsItem * parent)
	:QGraphicsItemGroup(parent), m_pBlock(_block)
{

}

AQSchemesEditor::AQSchemesEditor(QWidget *parent)
	: QWidget(parent), m_pScheme(0), m_pFile(0)
{
	ui.setupUi(this);

	QGraphicsScene * scene = new QGraphicsScene();
	ui.graphicsView->setScene(scene);
}

AQSchemesEditor::~AQSchemesEditor()
{

}

void AQSchemesEditor::openFile(AFile * file)
{
	//Load scheme from file
	AScheme * new_scheme = new AScheme();

	m_pFile = file;
	m_pScheme = new_scheme;

	updateScene();
}

void AQSchemesEditor::updateScene()
{
	ui.graphicsView->scene()->clear();

	for(auto i : m_pScheme->mBlocks)
	{
		AQBlock * block = new AQBlock(i);
		ui.graphicsView->scene()->addItem(block);
	}
}

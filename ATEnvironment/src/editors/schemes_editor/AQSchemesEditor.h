#ifndef AQSCHEMESEDITOR_H
#define AQSCHEMESEDITOR_H

#include <QWidget>
#include "ui_AQSchemesEditor.h"
#include <QGraphicsItemGroup>

class AFile;
namespace BlockScheme
{
	class AScheme;
	class ABlock;
};

namespace BlockScheme
{
	class AQBlock : public QGraphicsItemGroup
	{
	public:
		AQBlock(BlockScheme::ABlock * block, QGraphicsItem * parent = 0);
	private:
		BlockScheme::ABlock * m_pBlock;
	};
};

class AQSchemesEditor : public QWidget
{
	Q_OBJECT

public:
	AQSchemesEditor(QWidget *parent = 0);
	~AQSchemesEditor();
	void openFile(AFile * file);
	void updateScene();
private:
	Ui::AQSchemesEditor ui;

	BlockScheme::AScheme * m_pScheme;
	AFile * m_pFile;
};

#endif // AQSCHEMESEDITOR_H

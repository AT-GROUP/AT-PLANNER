#ifndef AOUPUTWIDGET_H
#define AOUPUTWIDGET_H

#include <QWidget>
#include "ui_AConsoleWidget.h"
#include <ATCore/AError.h>
#include <ATCore/ACommandExecutor.h>

class AConsoleWidget : public QWidget, public AErrorMessenger
{
	Q_OBJECT

public:
	AConsoleWidget(QWidget *parent = 0);
	~AConsoleWidget();
	void setDelegate(AIConsoleDelegate * _delegate);
	void printString(const std::string & str);
	
	//Messenger implementation
	virtual void criticalErrorOccured(const AError & error) override;
public slots:
	void commandExecutionRequested();
private:
	Ui::AConsoleWidget ui;
	AIConsoleDelegate * m_pDelegate;
};

#endif // AOUPUTWIDGET_H

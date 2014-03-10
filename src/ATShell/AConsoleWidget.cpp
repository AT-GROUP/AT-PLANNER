#include "AConsoleWidget.h"
#include <ATCore/AError.h>
#include <string>

using namespace std;

AConsoleWidget::AConsoleWidget(QWidget *parent)
	: QWidget(parent), m_pDelegate(nullptr)
{
	ui.setupUi(this);

	//Bind enter to command execution
	connect(ui.edInput, &QLineEdit::returnPressed, this, &AConsoleWidget::commandExecutionRequested);

	set_error_messenger(this);
}

AConsoleWidget::~AConsoleWidget()
{

}

void AConsoleWidget::setDelegate(AIConsoleDelegate * _delegate)
{
	m_pDelegate = _delegate;
}

void AConsoleWidget::printString(const std::string & str)
{
	ui.listWidget->addItem(QString::fromStdString(str));
}

void AConsoleWidget::commandExecutionRequested()
{
	if(m_pDelegate)
	{
		std::string script_body = ui.edInput->text().toStdString();
		std::string answer;
		AError err = m_pDelegate->executeScript(script_body, answer);
		if(err.OK())
		{
			ui.edInput->clear();
			printString(script_body);
			printString(answer);
		}
		else
		{
			printString("Error:" + answer);
		}
	}
	else
	{
		printString("Cannot execute command, interpreter not set.");
	}
}

void AConsoleWidget::criticalErrorOccured(const AError & error)
{
	printString("Error: " + string(error.text()));
}

void AConsoleWidget::printMessage(const std::string & msg)
{
	printString(msg);
}

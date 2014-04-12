#include <QtCore/QDir>
#include <QtWidgets>

#include "ADatastreamDialog.h"
#include "ADatastreamWidget.h"
#include "../ATCore/edfd/DFDConnection.h"

ADatastreamDialog::ADatastreamDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

void ADatastreamDialog::on_done_button_clicked()
{
	if (m_pConnection->std())
	{
		m_pConnection->clearSTD();
	}

	if (m_pConnection->dts())
	{
		m_pConnection->clearDTS();
	}
	
	if (ui.inc_data_list->count() > 0)
	{
		for(int i = 0; i < ui.inc_data_list->count(); ++i)
		{
			QListWidgetItem* item = ui.inc_data_list->item(i);
			m_pConnection->addDTS_data((item->text()).toStdString());
		}
	}
	if (ui.out_data_list->count() > 0)
	{
		for(int i = 0; i < ui.out_data_list->count(); ++i)
		{
			QListWidgetItem* item = ui.out_data_list->item(i);
			m_pConnection->addSTD_data((item->text()).toStdString());
		}
	}

	this->done(1);
}

void ADatastreamDialog::getConn(std::shared_ptr<DFDConnection> m_pConn)
{
	m_pConnection = m_pConn;
}

ADatastreamDialog::ADatastreamDialog(std::shared_ptr<DFDConnection> m_pConn)
{
	ui.setupUi(this);
	this->getConn(m_pConn);
	for(auto elem : m_pConnection->dts_d())
	{
		ui.inc_data_list->addItem(QString::fromStdString(elem));
	}
	for(auto elem : m_pConnection->std_d())
	{
		ui.out_data_list->addItem(QString::fromStdString(elem));
	}
}
#ifndef DFDDATASTREAM_DIALOG_H
#define DFDDATASTREAM_DIALOG_H

#include <QtWidgets>
#include <memory>
#include "ui_ADatastreamDialog.h"

class DFDConnection;

class ADatastreamDialog : public QDialog
{
	Q_OBJECT

public:
	ADatastreamDialog(QWidget *parent = 0);
	ADatastreamDialog(std::shared_ptr<DFDConnection> m_pConn);

	void getConn(std::shared_ptr<DFDConnection> m_pConn);

private slots:
	void on_done_button_clicked();

private:
	std::shared_ptr<DFDConnection> m_pConnection;
	Ui::ADatastreamDialog_dialogClass ui;
};

#endif // DFDDATASTREAM_DIALOG_H

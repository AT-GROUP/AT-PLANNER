#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

public slots:
    void NewFile();
    void Save();
    void SaveAs();
    void Load();

private:
	Ui::MainWindowClass *ui;
};

#endif // MAINWINDOW_H


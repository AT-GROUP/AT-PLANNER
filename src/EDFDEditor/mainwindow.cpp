#include <QAction>
#include <QFileDialog>
#include <QMenuBar>
#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

void MainWindow::NewFile()
{
    //Create new file
}

void MainWindow::SaveAs()
{
    //create new file and save to it
}

void MainWindow::Save()
{
    //rewrite existing file
}

void MainWindow::Load()
{
	//Load existing file
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindowClass)
{
    ui->setupUi(this);

    connect(ui->ANewFile, SIGNAL(triggered()), this, SLOT(NewFile()));

    connect(ui->ASave, SIGNAL(triggered()), this, SLOT(Save()));

    connect(ui->ASaveAs, SIGNAL(triggered()), this, SLOT(SaveAs()));

    connect(ui->ALoad, SIGNAL(triggered()), this, SLOT(Load()));

    connect(ui->AExit, SIGNAL(triggered()), this, SLOT(close()));

}

MainWindow::~MainWindow()
{
    delete ui;
}


/********************************************************************************
** Form generated from reading UI file 'ATEnvironment.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ATENVIRONMENT_H
#define UI_ATENVIRONMENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMdiArea>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "AOuputWidget.h"
#include "APlannerWidget.h"
#include "AProjectExplorer.h"

QT_BEGIN_NAMESPACE

class Ui_ATEnvironmentClass
{
public:
    QAction *actionNewProject;
    QAction *actionExit;
    QAction *actionAbout;
    QAction *actionOpen_Project;
    QAction *actionSave_Project;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QMdiArea *mdiArea;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuNew;
    QMenu *menuView;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *dwProjectExplorer;
    AProjectExplorer *wdgProjectExplorer;
    QVBoxLayout *verticalLayout;
    QDockWidget *dockWidget_2;
    APlannerWidget *dockWidgetContents_2;
    QDockWidget *dockWidget_3;
    AOuputWidget *dockWidgetContents_3;

    void setupUi(QMainWindow *ATEnvironmentClass)
    {
        if (ATEnvironmentClass->objectName().isEmpty())
            ATEnvironmentClass->setObjectName(QStringLiteral("ATEnvironmentClass"));
        ATEnvironmentClass->resize(997, 717);
        actionNewProject = new QAction(ATEnvironmentClass);
        actionNewProject->setObjectName(QStringLiteral("actionNewProject"));
        actionExit = new QAction(ATEnvironmentClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionAbout = new QAction(ATEnvironmentClass);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionOpen_Project = new QAction(ATEnvironmentClass);
        actionOpen_Project->setObjectName(QStringLiteral("actionOpen_Project"));
        actionSave_Project = new QAction(ATEnvironmentClass);
        actionSave_Project->setObjectName(QStringLiteral("actionSave_Project"));
        centralWidget = new QWidget(ATEnvironmentClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        mdiArea = new QMdiArea(centralWidget);
        mdiArea->setObjectName(QStringLiteral("mdiArea"));
        mdiArea->setViewMode(QMdiArea::TabbedView);
        mdiArea->setDocumentMode(true);
        mdiArea->setTabsClosable(true);
        mdiArea->setTabsMovable(true);

        horizontalLayout->addWidget(mdiArea);

        ATEnvironmentClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ATEnvironmentClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 997, 18));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuNew = new QMenu(menuFile);
        menuNew->setObjectName(QStringLiteral("menuNew"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QStringLiteral("menuView"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        ATEnvironmentClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ATEnvironmentClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ATEnvironmentClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ATEnvironmentClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ATEnvironmentClass->setStatusBar(statusBar);
        dwProjectExplorer = new QDockWidget(ATEnvironmentClass);
        dwProjectExplorer->setObjectName(QStringLiteral("dwProjectExplorer"));
        dwProjectExplorer->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
        wdgProjectExplorer = new AProjectExplorer();
        wdgProjectExplorer->setObjectName(QStringLiteral("wdgProjectExplorer"));
        verticalLayout = new QVBoxLayout(wdgProjectExplorer);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        dwProjectExplorer->setWidget(wdgProjectExplorer);
        ATEnvironmentClass->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dwProjectExplorer);
        dockWidget_2 = new QDockWidget(ATEnvironmentClass);
        dockWidget_2->setObjectName(QStringLiteral("dockWidget_2"));
        dockWidgetContents_2 = new APlannerWidget();
        dockWidgetContents_2->setObjectName(QStringLiteral("dockWidgetContents_2"));
        dockWidget_2->setWidget(dockWidgetContents_2);
        ATEnvironmentClass->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget_2);
        dockWidget_3 = new QDockWidget(ATEnvironmentClass);
        dockWidget_3->setObjectName(QStringLiteral("dockWidget_3"));
        dockWidget_3->setAllowedAreas(Qt::BottomDockWidgetArea);
        dockWidgetContents_3 = new AOuputWidget();
        dockWidgetContents_3->setObjectName(QStringLiteral("dockWidgetContents_3"));
        dockWidget_3->setWidget(dockWidgetContents_3);
        ATEnvironmentClass->addDockWidget(static_cast<Qt::DockWidgetArea>(8), dockWidget_3);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(menuNew->menuAction());
        menuFile->addAction(actionOpen_Project);
        menuFile->addAction(actionSave_Project);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuNew->addAction(actionNewProject);
        menuHelp->addAction(actionAbout);

        retranslateUi(ATEnvironmentClass);

        QMetaObject::connectSlotsByName(ATEnvironmentClass);
    } // setupUi

    void retranslateUi(QMainWindow *ATEnvironmentClass)
    {
        ATEnvironmentClass->setWindowTitle(QApplication::translate("ATEnvironmentClass", "ATEnvironment", 0));
        actionNewProject->setText(QApplication::translate("ATEnvironmentClass", "Project...", 0));
        actionExit->setText(QApplication::translate("ATEnvironmentClass", "Exit", 0));
        actionExit->setShortcut(QApplication::translate("ATEnvironmentClass", "Alt+F4", 0));
        actionAbout->setText(QApplication::translate("ATEnvironmentClass", "About", 0));
        actionOpen_Project->setText(QApplication::translate("ATEnvironmentClass", "Open Project...", 0));
        actionSave_Project->setText(QApplication::translate("ATEnvironmentClass", "Save Project", 0));
        menuFile->setTitle(QApplication::translate("ATEnvironmentClass", "File", 0));
        menuNew->setTitle(QApplication::translate("ATEnvironmentClass", "New", 0));
        menuView->setTitle(QApplication::translate("ATEnvironmentClass", "View", 0));
        menuHelp->setTitle(QApplication::translate("ATEnvironmentClass", "Help", 0));
        dwProjectExplorer->setWindowTitle(QApplication::translate("ATEnvironmentClass", "Project Explorer", 0));
        dockWidget_2->setWindowTitle(QApplication::translate("ATEnvironmentClass", "Planner", 0));
        dockWidget_3->setWindowTitle(QApplication::translate("ATEnvironmentClass", "Output", 0));
    } // retranslateUi

};

namespace Ui {
    class ATEnvironmentClass: public Ui_ATEnvironmentClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ATENVIRONMENT_H

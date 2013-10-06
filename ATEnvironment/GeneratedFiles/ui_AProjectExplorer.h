/********************************************************************************
** Form generated from reading UI file 'AProjectExplorer.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APROJECTEXPLORER_H
#define UI_APROJECTEXPLORER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "AQProjectTreeWidget.h"

QT_BEGIN_NAMESPACE

class Ui_AProjectExplorer
{
public:
    QVBoxLayout *verticalLayout;
    AQProjectTreeWidget *treeProject;

    void setupUi(QWidget *AProjectExplorer)
    {
        if (AProjectExplorer->objectName().isEmpty())
            AProjectExplorer->setObjectName(QStringLiteral("AProjectExplorer"));
        AProjectExplorer->resize(400, 300);
        verticalLayout = new QVBoxLayout(AProjectExplorer);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        treeProject = new AQProjectTreeWidget(AProjectExplorer);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeProject->setHeaderItem(__qtreewidgetitem);
        treeProject->setObjectName(QStringLiteral("treeProject"));
        treeProject->header()->setVisible(false);

        verticalLayout->addWidget(treeProject);


        retranslateUi(AProjectExplorer);

        QMetaObject::connectSlotsByName(AProjectExplorer);
    } // setupUi

    void retranslateUi(QWidget *AProjectExplorer)
    {
        AProjectExplorer->setWindowTitle(QApplication::translate("AProjectExplorer", "AProjectExplorer", 0));
    } // retranslateUi

};

namespace Ui {
    class AProjectExplorer: public Ui_AProjectExplorer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APROJECTEXPLORER_H

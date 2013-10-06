/********************************************************************************
** Form generated from reading UI file 'APlannerWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APLANNERWIDGET_H
#define UI_APLANNERWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_APlannerWidget
{
public:
    QVBoxLayout *verticalLayout;
    QTableWidget *tableWidget;

    void setupUi(QWidget *APlannerWidget)
    {
        if (APlannerWidget->objectName().isEmpty())
            APlannerWidget->setObjectName(QStringLiteral("APlannerWidget"));
        APlannerWidget->resize(400, 300);
        verticalLayout = new QVBoxLayout(APlannerWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        tableWidget = new QTableWidget(APlannerWidget);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));

        verticalLayout->addWidget(tableWidget);


        retranslateUi(APlannerWidget);

        QMetaObject::connectSlotsByName(APlannerWidget);
    } // setupUi

    void retranslateUi(QWidget *APlannerWidget)
    {
        APlannerWidget->setWindowTitle(QApplication::translate("APlannerWidget", "APlannerWidget", 0));
    } // retranslateUi

};

namespace Ui {
    class APlannerWidget: public Ui_APlannerWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APLANNERWIDGET_H

/********************************************************************************
** Form generated from reading UI file 'AOuputWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AOUPUTWIDGET_H
#define UI_AOUPUTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AOuputWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QListWidget *listWidget;

    void setupUi(QWidget *AOuputWidget)
    {
        if (AOuputWidget->objectName().isEmpty())
            AOuputWidget->setObjectName(QStringLiteral("AOuputWidget"));
        AOuputWidget->resize(550, 300);
        horizontalLayout = new QHBoxLayout(AOuputWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        listWidget = new QListWidget(AOuputWidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));

        horizontalLayout->addWidget(listWidget);


        retranslateUi(AOuputWidget);

        QMetaObject::connectSlotsByName(AOuputWidget);
    } // setupUi

    void retranslateUi(QWidget *AOuputWidget)
    {
        AOuputWidget->setWindowTitle(QApplication::translate("AOuputWidget", "AOuputWidget", 0));
    } // retranslateUi

};

namespace Ui {
    class AOuputWidget: public Ui_AOuputWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AOUPUTWIDGET_H

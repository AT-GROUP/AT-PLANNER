/********************************************************************************
** Form generated from reading UI file 'AQNewProjectDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AQNEWPROJECTDIALOG_H
#define UI_AQNEWPROJECTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_AQNewProjectDialog
{
public:
    QFormLayout *formLayout;
    QListWidget *listWidget;
    QPushButton *bnCancel;
    QPushButton *bnOK;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QLineEdit *edDirectory;
    QPushButton *bnSelectDirectory;
    QLabel *label_2;
    QLineEdit *edProjectName;

    void setupUi(QDialog *AQNewProjectDialog)
    {
        if (AQNewProjectDialog->objectName().isEmpty())
            AQNewProjectDialog->setObjectName(QStringLiteral("AQNewProjectDialog"));
        AQNewProjectDialog->resize(470, 292);
        formLayout = new QFormLayout(AQNewProjectDialog);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        listWidget = new QListWidget(AQNewProjectDialog);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));

        formLayout->setWidget(0, QFormLayout::SpanningRole, listWidget);

        bnCancel = new QPushButton(AQNewProjectDialog);
        bnCancel->setObjectName(QStringLiteral("bnCancel"));

        formLayout->setWidget(3, QFormLayout::LabelRole, bnCancel);

        bnOK = new QPushButton(AQNewProjectDialog);
        bnOK->setObjectName(QStringLiteral("bnOK"));

        formLayout->setWidget(3, QFormLayout::FieldRole, bnOK);

        label = new QLabel(AQNewProjectDialog);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        edDirectory = new QLineEdit(AQNewProjectDialog);
        edDirectory->setObjectName(QStringLiteral("edDirectory"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(edDirectory->sizePolicy().hasHeightForWidth());
        edDirectory->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(edDirectory);

        bnSelectDirectory = new QPushButton(AQNewProjectDialog);
        bnSelectDirectory->setObjectName(QStringLiteral("bnSelectDirectory"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(bnSelectDirectory->sizePolicy().hasHeightForWidth());
        bnSelectDirectory->setSizePolicy(sizePolicy1);
        bnSelectDirectory->setMinimumSize(QSize(30, 0));
        bnSelectDirectory->setMaximumSize(QSize(30, 16777215));

        horizontalLayout->addWidget(bnSelectDirectory);


        formLayout->setLayout(2, QFormLayout::FieldRole, horizontalLayout);

        label_2 = new QLabel(AQNewProjectDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        edProjectName = new QLineEdit(AQNewProjectDialog);
        edProjectName->setObjectName(QStringLiteral("edProjectName"));

        formLayout->setWidget(1, QFormLayout::FieldRole, edProjectName);


        retranslateUi(AQNewProjectDialog);

        QMetaObject::connectSlotsByName(AQNewProjectDialog);
    } // setupUi

    void retranslateUi(QDialog *AQNewProjectDialog)
    {
        AQNewProjectDialog->setWindowTitle(QApplication::translate("AQNewProjectDialog", "Create New Project...", 0));

        const bool __sortingEnabled = listWidget->isSortingEnabled();
        listWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("AQNewProjectDialog", "Integrated Expert System", 0));
        QListWidgetItem *___qlistwidgetitem1 = listWidget->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("AQNewProjectDialog", "Dynamic Integrated Expert System", 0));
        QListWidgetItem *___qlistwidgetitem2 = listWidget->item(2);
        ___qlistwidgetitem2->setText(QApplication::translate("AQNewProjectDialog", "Tutoring Integrated Expert System", 0));
        listWidget->setSortingEnabled(__sortingEnabled);

        bnCancel->setText(QApplication::translate("AQNewProjectDialog", "Cancel", 0));
        bnOK->setText(QApplication::translate("AQNewProjectDialog", "OK", 0));
        label->setText(QApplication::translate("AQNewProjectDialog", "Select Directory:", 0));
        edDirectory->setText(QApplication::translate("AQNewProjectDialog", "D:\\", 0));
        bnSelectDirectory->setText(QApplication::translate("AQNewProjectDialog", "...", 0));
        label_2->setText(QApplication::translate("AQNewProjectDialog", "Name:", 0));
        edProjectName->setText(QApplication::translate("AQNewProjectDialog", "NewProject1", 0));
    } // retranslateUi

};

namespace Ui {
    class AQNewProjectDialog: public Ui_AQNewProjectDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AQNEWPROJECTDIALOG_H

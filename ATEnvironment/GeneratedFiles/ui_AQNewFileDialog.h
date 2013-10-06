/********************************************************************************
** Form generated from reading UI file 'AQNewFileDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AQNEWFILEDIALOG_H
#define UI_AQNEWFILEDIALOG_H

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
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_AQNewFileDialog
{
public:
    QFormLayout *formLayout;
    QLabel *label;
    QListWidget *listWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *bnCancel;
    QPushButton *bnOK;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *edDirectory;
    QLineEdit *edFileName;

    void setupUi(QDialog *AQNewFileDialog)
    {
        if (AQNewFileDialog->objectName().isEmpty())
            AQNewFileDialog->setObjectName(QStringLiteral("AQNewFileDialog"));
        AQNewFileDialog->resize(400, 300);
        formLayout = new QFormLayout(AQNewFileDialog);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label = new QLabel(AQNewFileDialog);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        listWidget = new QListWidget(AQNewFileDialog);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));

        formLayout->setWidget(1, QFormLayout::SpanningRole, listWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        bnCancel = new QPushButton(AQNewFileDialog);
        bnCancel->setObjectName(QStringLiteral("bnCancel"));

        horizontalLayout->addWidget(bnCancel);

        bnOK = new QPushButton(AQNewFileDialog);
        bnOK->setObjectName(QStringLiteral("bnOK"));

        horizontalLayout->addWidget(bnOK);


        formLayout->setLayout(4, QFormLayout::SpanningRole, horizontalLayout);

        label_2 = new QLabel(AQNewFileDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_2);

        label_3 = new QLabel(AQNewFileDialog);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_3);

        edDirectory = new QLineEdit(AQNewFileDialog);
        edDirectory->setObjectName(QStringLiteral("edDirectory"));

        formLayout->setWidget(2, QFormLayout::FieldRole, edDirectory);

        edFileName = new QLineEdit(AQNewFileDialog);
        edFileName->setObjectName(QStringLiteral("edFileName"));

        formLayout->setWidget(3, QFormLayout::FieldRole, edFileName);


        retranslateUi(AQNewFileDialog);

        QMetaObject::connectSlotsByName(AQNewFileDialog);
    } // setupUi

    void retranslateUi(QDialog *AQNewFileDialog)
    {
        AQNewFileDialog->setWindowTitle(QApplication::translate("AQNewFileDialog", "Create new item", 0));
        label->setText(QApplication::translate("AQNewFileDialog", "Select file type", 0));

        const bool __sortingEnabled = listWidget->isSortingEnabled();
        listWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("AQNewFileDialog", "Scheme/Data Diagram", 0));
        QListWidgetItem *___qlistwidgetitem1 = listWidget->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("AQNewFileDialog", "Knowledge Base", 0));
        QListWidgetItem *___qlistwidgetitem2 = listWidget->item(2);
        ___qlistwidgetitem2->setText(QApplication::translate("AQNewFileDialog", "Dialog Scenario", 0));
        listWidget->setSortingEnabled(__sortingEnabled);

        bnCancel->setText(QApplication::translate("AQNewFileDialog", "Cancel", 0));
        bnOK->setText(QApplication::translate("AQNewFileDialog", "OK", 0));
        label_2->setText(QApplication::translate("AQNewFileDialog", "Directory:", 0));
        label_3->setText(QApplication::translate("AQNewFileDialog", "File name:", 0));
        edFileName->setText(QApplication::translate("AQNewFileDialog", "NewFile1", 0));
    } // retranslateUi

};

namespace Ui {
    class AQNewFileDialog: public Ui_AQNewFileDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AQNEWFILEDIALOG_H

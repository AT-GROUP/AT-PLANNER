/********************************************************************************
** Form generated from reading UI file 'AQSchemesEditor.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AQSCHEMESEDITOR_H
#define UI_AQSCHEMESEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AQSchemesEditor
{
public:
    QHBoxLayout *horizontalLayout;
    QGraphicsView *graphicsView;

    void setupUi(QWidget *AQSchemesEditor)
    {
        if (AQSchemesEditor->objectName().isEmpty())
            AQSchemesEditor->setObjectName(QStringLiteral("AQSchemesEditor"));
        AQSchemesEditor->resize(578, 300);
        horizontalLayout = new QHBoxLayout(AQSchemesEditor);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        graphicsView = new QGraphicsView(AQSchemesEditor);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));

        horizontalLayout->addWidget(graphicsView);


        retranslateUi(AQSchemesEditor);

        QMetaObject::connectSlotsByName(AQSchemesEditor);
    } // setupUi

    void retranslateUi(QWidget *AQSchemesEditor)
    {
        AQSchemesEditor->setWindowTitle(QApplication::translate("AQSchemesEditor", "AQSchemesEditor", 0));
    } // retranslateUi

};

namespace Ui {
    class AQSchemesEditor: public Ui_AQSchemesEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AQSCHEMESEDITOR_H

/********************************************************************************
** Form generated from reading UI file 'tp1mg2.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TP1MG2_H
#define UI_TP1MG2_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TP1MG2Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TP1MG2Class)
    {
        if (TP1MG2Class->objectName().isEmpty())
            TP1MG2Class->setObjectName(QStringLiteral("TP1MG2Class"));
        TP1MG2Class->resize(600, 400);
        menuBar = new QMenuBar(TP1MG2Class);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        TP1MG2Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(TP1MG2Class);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        TP1MG2Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(TP1MG2Class);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        TP1MG2Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(TP1MG2Class);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        TP1MG2Class->setStatusBar(statusBar);

        retranslateUi(TP1MG2Class);

        QMetaObject::connectSlotsByName(TP1MG2Class);
    } // setupUi

    void retranslateUi(QMainWindow *TP1MG2Class)
    {
        TP1MG2Class->setWindowTitle(QApplication::translate("TP1MG2Class", "TP1MG2", 0));
    } // retranslateUi

};

namespace Ui {
    class TP1MG2Class: public Ui_TP1MG2Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TP1MG2_H

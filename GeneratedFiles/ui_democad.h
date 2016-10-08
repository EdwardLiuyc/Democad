/********************************************************************************
** Form generated from reading UI file 'democad.ui'
**
** Created: Mon Sep 26 14:56:06 2016
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEMOCAD_H
#define UI_DEMOCAD_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DemoCad
{
public:
    QWidget *centralWidget;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *DemoCad)
    {
        if (DemoCad->objectName().isEmpty())
            DemoCad->setObjectName(QString::fromUtf8("DemoCad"));
        DemoCad->resize(600, 600);
        centralWidget = new QWidget(DemoCad);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        DemoCad->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(DemoCad);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 23));
        DemoCad->setMenuBar(menuBar);

        retranslateUi(DemoCad);

        QMetaObject::connectSlotsByName(DemoCad);
    } // setupUi

    void retranslateUi(QMainWindow *DemoCad)
    {
        DemoCad->setWindowTitle(QApplication::translate("DemoCad", "DemoCad", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DemoCad: public Ui_DemoCad {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEMOCAD_H

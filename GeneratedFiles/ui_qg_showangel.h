/********************************************************************************
** Form generated from reading UI file 'qg_showangel.ui'
**
** Created: Mon Sep 26 14:56:11 2016
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QG_SHOWANGEL_H
#define UI_QG_SHOWANGEL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QG_ShowAngel
{
public:
    QGridLayout *gridLayout;
    QLabel *label_16;
    QLineEdit *LED_showangel;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *QG_ShowAngel)
    {
        if (QG_ShowAngel->objectName().isEmpty())
            QG_ShowAngel->setObjectName(QString::fromUtf8("QG_ShowAngel"));
        QG_ShowAngel->resize(519, 20);
        QG_ShowAngel->setMinimumSize(QSize(519, 0));
        gridLayout = new QGridLayout(QG_ShowAngel);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_16 = new QLabel(QG_ShowAngel);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        gridLayout->addWidget(label_16, 0, 0, 1, 1);

        LED_showangel = new QLineEdit(QG_ShowAngel);
        LED_showangel->setObjectName(QString::fromUtf8("LED_showangel"));
        LED_showangel->setMaximumSize(QSize(80, 16777215));

        gridLayout->addWidget(LED_showangel, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(370, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 2, 1, 1);


        retranslateUi(QG_ShowAngel);

        QMetaObject::connectSlotsByName(QG_ShowAngel);
    } // setupUi

    void retranslateUi(QWidget *QG_ShowAngel)
    {
        QG_ShowAngel->setWindowTitle(QApplication::translate("QG_ShowAngel", "Form", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("QG_ShowAngel", "\350\247\222\345\272\246", 0, QApplication::UnicodeUTF8));
        LED_showangel->setText(QApplication::translate("QG_ShowAngel", "0", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QG_ShowAngel: public Ui_QG_ShowAngel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QG_SHOWANGEL_H

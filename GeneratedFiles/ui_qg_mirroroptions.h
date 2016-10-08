/********************************************************************************
** Form generated from reading UI file 'qg_mirroroptions.ui'
**
** Created: Mon Sep 26 14:56:11 2016
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QG_MIRROROPTIONS_H
#define UI_QG_MIRROROPTIONS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QG_MirrorOptions
{
public:
    QLabel *lbInfo;
    QRadioButton *radioButton_manual;
    QRadioButton *radioButton_xAxlis;
    QRadioButton *radioButton_yAxlis;
    QPushButton *pushButton_ok;

    void setupUi(QWidget *QG_MirrorOptions)
    {
        if (QG_MirrorOptions->objectName().isEmpty())
            QG_MirrorOptions->setObjectName(QString::fromUtf8("QG_MirrorOptions"));
        QG_MirrorOptions->resize(450, 37);
        lbInfo = new QLabel(QG_MirrorOptions);
        lbInfo->setObjectName(QString::fromUtf8("lbInfo"));
        lbInfo->setGeometry(QRect(10, 10, 75, 16));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font.setPointSize(12);
        font.setBold(false);
        font.setWeight(50);
        lbInfo->setFont(font);
        radioButton_manual = new QRadioButton(QG_MirrorOptions);
        radioButton_manual->setObjectName(QString::fromUtf8("radioButton_manual"));
        radioButton_manual->setGeometry(QRect(90, 10, 51, 20));
        QFont font1;
        font1.setPointSize(12);
        radioButton_manual->setFont(font1);
        radioButton_xAxlis = new QRadioButton(QG_MirrorOptions);
        radioButton_xAxlis->setObjectName(QString::fromUtf8("radioButton_xAxlis"));
        radioButton_xAxlis->setGeometry(QRect(150, 10, 61, 20));
        radioButton_xAxlis->setFont(font1);
        radioButton_yAxlis = new QRadioButton(QG_MirrorOptions);
        radioButton_yAxlis->setObjectName(QString::fromUtf8("radioButton_yAxlis"));
        radioButton_yAxlis->setGeometry(QRect(220, 10, 61, 20));
        radioButton_yAxlis->setFont(font1);
        pushButton_ok = new QPushButton(QG_MirrorOptions);
        pushButton_ok->setObjectName(QString::fromUtf8("pushButton_ok"));
        pushButton_ok->setGeometry(QRect(290, 8, 61, 23));
        pushButton_ok->setFont(font1);

        retranslateUi(QG_MirrorOptions);
        QObject::connect(radioButton_manual, SIGNAL(clicked()), QG_MirrorOptions, SLOT(changeSelect()));
        QObject::connect(radioButton_xAxlis, SIGNAL(clicked()), QG_MirrorOptions, SLOT(changeSelect()));
        QObject::connect(radioButton_yAxlis, SIGNAL(clicked()), QG_MirrorOptions, SLOT(changeSelect()));
        QObject::connect(pushButton_ok, SIGNAL(clicked()), QG_MirrorOptions, SLOT(mirrorFixed()));

        QMetaObject::connectSlotsByName(QG_MirrorOptions);
    } // setupUi

    void retranslateUi(QWidget *QG_MirrorOptions)
    {
        QG_MirrorOptions->setWindowTitle(QApplication::translate("QG_MirrorOptions", "Form", 0, QApplication::UnicodeUTF8));
        lbInfo->setText(QApplication::translate("QG_MirrorOptions", "\351\225\234\345\203\217\345\217\202\346\225\260:", 0, QApplication::UnicodeUTF8));
        radioButton_manual->setText(QApplication::translate("QG_MirrorOptions", "\346\211\213\345\212\250", 0, QApplication::UnicodeUTF8));
        radioButton_xAxlis->setText(QApplication::translate("QG_MirrorOptions", "X\345\257\271\347\247\260", 0, QApplication::UnicodeUTF8));
        radioButton_yAxlis->setText(QApplication::translate("QG_MirrorOptions", "Y\345\257\271\347\247\260", 0, QApplication::UnicodeUTF8));
        pushButton_ok->setText(QApplication::translate("QG_MirrorOptions", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QG_MirrorOptions: public Ui_QG_MirrorOptions {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QG_MIRROROPTIONS_H

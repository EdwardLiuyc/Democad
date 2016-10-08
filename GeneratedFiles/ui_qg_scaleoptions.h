/********************************************************************************
** Form generated from reading UI file 'qg_scaleoptions.ui'
**
** Created: Mon Sep 26 14:56:11 2016
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QG_SCALEOPTIONS_H
#define UI_QG_SCALEOPTIONS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QG_ScaleOptions
{
public:
    QLabel *lbInfo;
    QRadioButton *radioButton_manual;
    QRadioButton *radioButton_fixed;
    QPushButton *pushButton_ok;
    QLabel *label_6;
    QLabel *label_2;
    QLineEdit *lineEdit_xBaseValue;
    QLabel *label_3;
    QLineEdit *lineEdit_yBaseValue;
    QLabel *label_7;
    QLabel *label_4;
    QLineEdit *lineEdit_xFactorValue;
    QLabel *label_5;
    QLineEdit *lineEdit_yFactorValue;

    void setupUi(QWidget *QG_ScaleOptions)
    {
        if (QG_ScaleOptions->objectName().isEmpty())
            QG_ScaleOptions->setObjectName(QString::fromUtf8("QG_ScaleOptions"));
        QG_ScaleOptions->resize(552, 37);
        lbInfo = new QLabel(QG_ScaleOptions);
        lbInfo->setObjectName(QString::fromUtf8("lbInfo"));
        lbInfo->setGeometry(QRect(1, 10, 75, 16));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font.setPointSize(11);
        font.setBold(false);
        font.setWeight(50);
        lbInfo->setFont(font);
        radioButton_manual = new QRadioButton(QG_ScaleOptions);
        radioButton_manual->setObjectName(QString::fromUtf8("radioButton_manual"));
        radioButton_manual->setGeometry(QRect(81, 11, 50, 16));
        QFont font1;
        font1.setPointSize(11);
        radioButton_manual->setFont(font1);
        radioButton_fixed = new QRadioButton(QG_ScaleOptions);
        radioButton_fixed->setObjectName(QString::fromUtf8("radioButton_fixed"));
        radioButton_fixed->setGeometry(QRect(132, 11, 50, 16));
        radioButton_fixed->setFont(font1);
        pushButton_ok = new QPushButton(QG_ScaleOptions);
        pushButton_ok->setObjectName(QString::fromUtf8("pushButton_ok"));
        pushButton_ok->setGeometry(QRect(500, 8, 41, 23));
        pushButton_ok->setFont(font1);
        label_6 = new QLabel(QG_ScaleOptions);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(185, 11, 30, 16));
        label_6->setFont(font1);
        label_2 = new QLabel(QG_ScaleOptions);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(219, 11, 16, 16));
        label_2->setFont(font1);
        lineEdit_xBaseValue = new QLineEdit(QG_ScaleOptions);
        lineEdit_xBaseValue->setObjectName(QString::fromUtf8("lineEdit_xBaseValue"));
        lineEdit_xBaseValue->setGeometry(QRect(233, 9, 46, 20));
        lineEdit_xBaseValue->setFont(font1);
        lineEdit_xBaseValue->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_3 = new QLabel(QG_ScaleOptions);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(281, 11, 16, 16));
        label_3->setFont(font1);
        lineEdit_yBaseValue = new QLineEdit(QG_ScaleOptions);
        lineEdit_yBaseValue->setObjectName(QString::fromUtf8("lineEdit_yBaseValue"));
        lineEdit_yBaseValue->setGeometry(QRect(295, 9, 47, 20));
        lineEdit_yBaseValue->setFont(font1);
        lineEdit_yBaseValue->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_7 = new QLabel(QG_ScaleOptions);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(345, 9, 31, 20));
        label_7->setFont(font1);
        label_4 = new QLabel(QG_ScaleOptions);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(377, 11, 16, 16));
        label_4->setFont(font1);
        lineEdit_xFactorValue = new QLineEdit(QG_ScaleOptions);
        lineEdit_xFactorValue->setObjectName(QString::fromUtf8("lineEdit_xFactorValue"));
        lineEdit_xFactorValue->setGeometry(QRect(390, 9, 46, 20));
        lineEdit_xFactorValue->setFont(font1);
        lineEdit_xFactorValue->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_5 = new QLabel(QG_ScaleOptions);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(438, 11, 16, 16));
        label_5->setFont(font1);
        lineEdit_yFactorValue = new QLineEdit(QG_ScaleOptions);
        lineEdit_yFactorValue->setObjectName(QString::fromUtf8("lineEdit_yFactorValue"));
        lineEdit_yFactorValue->setGeometry(QRect(451, 9, 47, 20));
        lineEdit_yFactorValue->setFont(font1);
        lineEdit_yFactorValue->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        retranslateUi(QG_ScaleOptions);
        QObject::connect(radioButton_manual, SIGNAL(clicked()), QG_ScaleOptions, SLOT(changeSelect()));
        QObject::connect(radioButton_fixed, SIGNAL(clicked()), QG_ScaleOptions, SLOT(changeSelect()));
        QObject::connect(pushButton_ok, SIGNAL(clicked()), QG_ScaleOptions, SLOT(scaleFixed()));

        QMetaObject::connectSlotsByName(QG_ScaleOptions);
    } // setupUi

    void retranslateUi(QWidget *QG_ScaleOptions)
    {
        QG_ScaleOptions->setWindowTitle(QApplication::translate("QG_ScaleOptions", "Form", 0, QApplication::UnicodeUTF8));
        lbInfo->setText(QApplication::translate("QG_ScaleOptions", "\347\274\251\346\224\276\345\217\202\346\225\260:", 0, QApplication::UnicodeUTF8));
        radioButton_manual->setText(QApplication::translate("QG_ScaleOptions", "\346\211\213\345\212\250", 0, QApplication::UnicodeUTF8));
        radioButton_fixed->setText(QApplication::translate("QG_ScaleOptions", "\345\233\272\345\256\232", 0, QApplication::UnicodeUTF8));
        pushButton_ok->setText(QApplication::translate("QG_ScaleOptions", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("QG_ScaleOptions", "\345\237\272\347\202\271", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("QG_ScaleOptions", "X:", 0, QApplication::UnicodeUTF8));
        lineEdit_xBaseValue->setText(QApplication::translate("QG_ScaleOptions", "0", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("QG_ScaleOptions", "Y:", 0, QApplication::UnicodeUTF8));
        lineEdit_yBaseValue->setText(QApplication::translate("QG_ScaleOptions", "0", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("QG_ScaleOptions", "\346\257\224\344\276\213", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("QG_ScaleOptions", "X:", 0, QApplication::UnicodeUTF8));
        lineEdit_xFactorValue->setText(QApplication::translate("QG_ScaleOptions", "0", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("QG_ScaleOptions", "Y:", 0, QApplication::UnicodeUTF8));
        lineEdit_yFactorValue->setText(QApplication::translate("QG_ScaleOptions", "0", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QG_ScaleOptions: public Ui_QG_ScaleOptions {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QG_SCALEOPTIONS_H

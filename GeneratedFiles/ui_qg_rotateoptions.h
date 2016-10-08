/********************************************************************************
** Form generated from reading UI file 'qg_rotateoptions.ui'
**
** Created: Mon Sep 26 14:56:11 2016
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QG_ROTATEOPTIONS_H
#define UI_QG_ROTATEOPTIONS_H

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

class Ui_QG_RotateOptions
{
public:
    QLabel *lbInfo;
    QRadioButton *radioButton_manual;
    QRadioButton *radioButton_fixed;
    QPushButton *pushButton_ok;
    QLabel *label_2;
    QLineEdit *lineEdit_xValue;
    QLabel *label_4;
    QLineEdit *lineEdit_angle;
    QLabel *label_3;
    QLineEdit *lineEdit_yValue;

    void setupUi(QWidget *QG_RotateOptions)
    {
        if (QG_RotateOptions->objectName().isEmpty())
            QG_RotateOptions->setObjectName(QString::fromUtf8("QG_RotateOptions"));
        QG_RotateOptions->resize(500, 37);
        lbInfo = new QLabel(QG_RotateOptions);
        lbInfo->setObjectName(QString::fromUtf8("lbInfo"));
        lbInfo->setGeometry(QRect(3, 10, 75, 16));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font.setPointSize(12);
        font.setBold(false);
        font.setWeight(50);
        lbInfo->setFont(font);
        radioButton_manual = new QRadioButton(QG_RotateOptions);
        radioButton_manual->setObjectName(QString::fromUtf8("radioButton_manual"));
        radioButton_manual->setGeometry(QRect(81, 10, 51, 16));
        QFont font1;
        font1.setPointSize(12);
        radioButton_manual->setFont(font1);
        radioButton_fixed = new QRadioButton(QG_RotateOptions);
        radioButton_fixed->setObjectName(QString::fromUtf8("radioButton_fixed"));
        radioButton_fixed->setGeometry(QRect(134, 10, 50, 16));
        radioButton_fixed->setFont(font1);
        pushButton_ok = new QPushButton(QG_RotateOptions);
        pushButton_ok->setObjectName(QString::fromUtf8("pushButton_ok"));
        pushButton_ok->setGeometry(QRect(440, 6, 50, 25));
        pushButton_ok->setFont(font1);
        label_2 = new QLabel(QG_RotateOptions);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(192, 10, 16, 16));
        label_2->setFont(font1);
        lineEdit_xValue = new QLineEdit(QG_RotateOptions);
        lineEdit_xValue->setObjectName(QString::fromUtf8("lineEdit_xValue"));
        lineEdit_xValue->setGeometry(QRect(210, 8, 50, 23));
        lineEdit_xValue->setFont(font1);
        lineEdit_xValue->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_4 = new QLabel(QG_RotateOptions);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(347, 9, 35, 20));
        label_4->setFont(font1);
        lineEdit_angle = new QLineEdit(QG_RotateOptions);
        lineEdit_angle->setObjectName(QString::fromUtf8("lineEdit_angle"));
        lineEdit_angle->setGeometry(QRect(383, 8, 50, 23));
        lineEdit_angle->setFont(font1);
        lineEdit_angle->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_3 = new QLabel(QG_RotateOptions);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(270, 11, 16, 16));
        label_3->setFont(font1);
        lineEdit_yValue = new QLineEdit(QG_RotateOptions);
        lineEdit_yValue->setObjectName(QString::fromUtf8("lineEdit_yValue"));
        lineEdit_yValue->setGeometry(QRect(286, 8, 50, 23));
        lineEdit_yValue->setFont(font1);
        lineEdit_yValue->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        retranslateUi(QG_RotateOptions);
        QObject::connect(radioButton_manual, SIGNAL(clicked()), QG_RotateOptions, SLOT(changeSelect()));
        QObject::connect(radioButton_fixed, SIGNAL(clicked()), QG_RotateOptions, SLOT(changeSelect()));
        QObject::connect(pushButton_ok, SIGNAL(clicked()), QG_RotateOptions, SLOT(rotateFixed()));

        QMetaObject::connectSlotsByName(QG_RotateOptions);
    } // setupUi

    void retranslateUi(QWidget *QG_RotateOptions)
    {
        QG_RotateOptions->setWindowTitle(QApplication::translate("QG_RotateOptions", "Form", 0, QApplication::UnicodeUTF8));
        lbInfo->setText(QApplication::translate("QG_RotateOptions", "\346\227\213\350\275\254\345\217\202\346\225\260:", 0, QApplication::UnicodeUTF8));
        radioButton_manual->setText(QApplication::translate("QG_RotateOptions", "\346\211\213\345\212\250", 0, QApplication::UnicodeUTF8));
        radioButton_fixed->setText(QApplication::translate("QG_RotateOptions", "\350\207\252\345\212\250", 0, QApplication::UnicodeUTF8));
        pushButton_ok->setText(QApplication::translate("QG_RotateOptions", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("QG_RotateOptions", "X:", 0, QApplication::UnicodeUTF8));
        lineEdit_xValue->setText(QApplication::translate("QG_RotateOptions", "0", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("QG_RotateOptions", "\350\247\222\345\272\246", 0, QApplication::UnicodeUTF8));
        lineEdit_angle->setText(QApplication::translate("QG_RotateOptions", "0", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("QG_RotateOptions", "Y:", 0, QApplication::UnicodeUTF8));
        lineEdit_yValue->setText(QApplication::translate("QG_RotateOptions", "0", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QG_RotateOptions: public Ui_QG_RotateOptions {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QG_ROTATEOPTIONS_H

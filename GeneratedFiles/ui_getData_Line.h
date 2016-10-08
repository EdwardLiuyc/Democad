/********************************************************************************
** Form generated from reading UI file 'getData_Line.ui'
**
** Created: Mon Sep 26 14:56:11 2016
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GETDATA_LINE_H
#define UI_GETDATA_LINE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QLineEdit *lineEdit_X;
    QLabel *label_X;
    QLineEdit *lineEdit_Y;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(381, 20);
        Form->setFocusPolicy(Qt::StrongFocus);
        lineEdit_X = new QLineEdit(Form);
        lineEdit_X->setObjectName(QString::fromUtf8("lineEdit_X"));
        lineEdit_X->setGeometry(QRect(120, 0, 128, 20));
        QFont font;
        font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font.setPointSize(10);
        lineEdit_X->setFont(font);
        lineEdit_X->setFocusPolicy(Qt::TabFocus);
        lineEdit_X->setCursorPosition(0);
        lineEdit_X->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_X = new QLabel(Form);
        label_X->setObjectName(QString::fromUtf8("label_X"));
        label_X->setGeometry(QRect(0, 0, 118, 20));
        label_X->setFont(font);
        label_X->setFrameShape(QFrame::NoFrame);
        lineEdit_Y = new QLineEdit(Form);
        lineEdit_Y->setObjectName(QString::fromUtf8("lineEdit_Y"));
        lineEdit_Y->setGeometry(QRect(250, 0, 128, 20));
        lineEdit_Y->setFont(font);
        lineEdit_Y->setFocusPolicy(Qt::TabFocus);
        lineEdit_Y->setCursorPosition(0);
        lineEdit_Y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", 0, QApplication::UnicodeUTF8));
        lineEdit_X->setText(QString());
        label_X->setText(QApplication::translate("Form", "\350\257\267\350\276\223\345\205\245\350\265\267\347\202\271\345\235\220\346\240\207\357\274\232", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GETDATA_LINE_H

/********************************************************************************
** Form generated from reading UI file 'ErrorMessage.ui'
**
** Created: Mon Sep 26 14:56:11 2016
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ERRORMESSAGE_H
#define UI_ERRORMESSAGE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_ErrorMessage
{
public:
    QTextEdit *lbDescription;
    QGroupBox *groupBox;
    QGroupBox *groupBox_2;
    QPushButton *btnNo;
    QPushButton *btnFouthChoose;
    QPushButton *btnYes;
    QPushButton *btnThirdChoose;
    QCheckBox *checkBox;
    QGroupBox *groupBox_3;
    QLabel *lbErrorNum;
    QLabel *lbErrorValue;

    void setupUi(QDialog *ErrorMessage)
    {
        if (ErrorMessage->objectName().isEmpty())
            ErrorMessage->setObjectName(QString::fromUtf8("ErrorMessage"));
        ErrorMessage->resize(500, 292);
        ErrorMessage->setMinimumSize(QSize(500, 292));
        ErrorMessage->setMaximumSize(QSize(500, 292));
        ErrorMessage->setModal(true);
        lbDescription = new QTextEdit(ErrorMessage);
        lbDescription->setObjectName(QString::fromUtf8("lbDescription"));
        lbDescription->setGeometry(QRect(20, 44, 461, 201));
        lbDescription->setContextMenuPolicy(Qt::NoContextMenu);
        lbDescription->setStyleSheet(QString::fromUtf8(""));
        lbDescription->setReadOnly(true);
        groupBox = new QGroupBox(ErrorMessage);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 4, 481, 247));
        groupBox_2 = new QGroupBox(ErrorMessage);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 254, 481, 35));
        btnNo = new QPushButton(groupBox_2);
        btnNo->setObjectName(QString::fromUtf8("btnNo"));
        btnNo->setGeometry(QRect(410, 5, 61, 25));
        btnFouthChoose = new QPushButton(groupBox_2);
        btnFouthChoose->setObjectName(QString::fromUtf8("btnFouthChoose"));
        btnFouthChoose->setGeometry(QRect(200, 5, 61, 25));
        btnYes = new QPushButton(groupBox_2);
        btnYes->setObjectName(QString::fromUtf8("btnYes"));
        btnYes->setGeometry(QRect(340, 5, 61, 25));
        btnThirdChoose = new QPushButton(groupBox_2);
        btnThirdChoose->setObjectName(QString::fromUtf8("btnThirdChoose"));
        btnThirdChoose->setGeometry(QRect(270, 5, 61, 25));
        checkBox = new QCheckBox(groupBox_2);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(10, 9, 171, 16));
        groupBox_3 = new QGroupBox(ErrorMessage);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(20, 9, 461, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font.setPointSize(12);
        groupBox_3->setFont(font);
        lbErrorNum = new QLabel(groupBox_3);
        lbErrorNum->setObjectName(QString::fromUtf8("lbErrorNum"));
        lbErrorNum->setGeometry(QRect(0, 0, 81, 31));
        QFont font1;
        font1.setPointSize(15);
        lbErrorNum->setFont(font1);
        lbErrorNum->setAlignment(Qt::AlignCenter);
        lbErrorValue = new QLabel(groupBox_3);
        lbErrorValue->setObjectName(QString::fromUtf8("lbErrorValue"));
        lbErrorValue->setGeometry(QRect(70, 0, 61, 31));
        lbErrorValue->setFont(font1);
        lbErrorValue->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        groupBox_2->raise();
        groupBox->raise();
        lbDescription->raise();
        groupBox_3->raise();

        retranslateUi(ErrorMessage);

        QMetaObject::connectSlotsByName(ErrorMessage);
    } // setupUi

    void retranslateUi(QDialog *ErrorMessage)
    {
        ErrorMessage->setWindowTitle(QApplication::translate("ErrorMessage", "ErrorMessage", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QString());
        groupBox_2->setTitle(QString());
        btnNo->setText(QApplication::translate("ErrorMessage", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
        btnFouthChoose->setText(QApplication::translate("ErrorMessage", "PushButton", 0, QApplication::UnicodeUTF8));
        btnYes->setText(QApplication::translate("ErrorMessage", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        btnThirdChoose->setText(QApplication::translate("ErrorMessage", "PushButton", 0, QApplication::UnicodeUTF8));
        checkBox->setText(QApplication::translate("ErrorMessage", "\344\270\272\344\271\213\345\220\216\345\206\262\347\252\201\346\211\247\350\241\214\346\255\244\346\223\215\344\275\234", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QString());
        lbErrorNum->setText(QApplication::translate("ErrorMessage", "\351\224\231\350\257\257\345\217\267:", 0, QApplication::UnicodeUTF8));
        lbErrorValue->setText(QApplication::translate("ErrorMessage", "10001", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ErrorMessage: public Ui_ErrorMessage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ERRORMESSAGE_H

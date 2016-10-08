/********************************************************************************
** Form generated from reading UI file 'qg_moveoptions.ui'
**
** Created: Mon Sep 26 14:56:11 2016
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QG_MOVEOPTIONS_H
#define UI_QG_MOVEOPTIONS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QG_MoveOptions
{
public:
    QLabel *lbInfo;
    QRadioButton *radioButton_manual;
    QRadioButton *radioButton_fixed;
    QFrame *line;
    QLabel *label;
    QLineEdit *lineEdit_xValue;
    QLabel *label_2;
    QLineEdit *lineEdit_yValue;
    QPushButton *pushButton_ok;

    void setupUi(QWidget *QG_MoveOptions)
    {
        if (QG_MoveOptions->objectName().isEmpty())
            QG_MoveOptions->setObjectName(QString::fromUtf8("QG_MoveOptions"));
        QG_MoveOptions->resize(626, 37);
        QFont font;
        font.setPointSize(12);
        QG_MoveOptions->setFont(font);
        lbInfo = new QLabel(QG_MoveOptions);
        lbInfo->setObjectName(QString::fromUtf8("lbInfo"));
        lbInfo->setGeometry(QRect(6, 10, 75, 16));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font1.setPointSize(12);
        font1.setBold(false);
        font1.setWeight(50);
        lbInfo->setFont(font1);
        radioButton_manual = new QRadioButton(QG_MoveOptions);
        radioButton_manual->setObjectName(QString::fromUtf8("radioButton_manual"));
        radioButton_manual->setGeometry(QRect(80, 10, 51, 16));
        radioButton_manual->setFont(font1);
        radioButton_fixed = new QRadioButton(QG_MoveOptions);
        radioButton_fixed->setObjectName(QString::fromUtf8("radioButton_fixed"));
        radioButton_fixed->setGeometry(QRect(134, 10, 51, 16));
        radioButton_fixed->setFont(font1);
        line = new QFrame(QG_MoveOptions);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(181, 8, 20, 23));
        line->setMinimumSize(QSize(20, 0));
        line->setFont(font1);
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        label = new QLabel(QG_MoveOptions);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(200, 10, 16, 16));
        label->setFont(font1);
        lineEdit_xValue = new QLineEdit(QG_MoveOptions);
        lineEdit_xValue->setObjectName(QString::fromUtf8("lineEdit_xValue"));
        lineEdit_xValue->setGeometry(QRect(219, 8, 85, 23));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEdit_xValue->sizePolicy().hasHeightForWidth());
        lineEdit_xValue->setSizePolicy(sizePolicy);
        lineEdit_xValue->setFont(font1);
        lineEdit_xValue->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_2 = new QLabel(QG_MoveOptions);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(312, 10, 16, 16));
        label_2->setFont(font1);
        lineEdit_yValue = new QLineEdit(QG_MoveOptions);
        lineEdit_yValue->setObjectName(QString::fromUtf8("lineEdit_yValue"));
        lineEdit_yValue->setGeometry(QRect(330, 8, 85, 23));
        sizePolicy.setHeightForWidth(lineEdit_yValue->sizePolicy().hasHeightForWidth());
        lineEdit_yValue->setSizePolicy(sizePolicy);
        lineEdit_yValue->setFont(font1);
        lineEdit_yValue->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        pushButton_ok = new QPushButton(QG_MoveOptions);
        pushButton_ok->setObjectName(QString::fromUtf8("pushButton_ok"));
        pushButton_ok->setGeometry(QRect(430, 6, 50, 25));
        pushButton_ok->setFont(font1);

        retranslateUi(QG_MoveOptions);
        QObject::connect(radioButton_manual, SIGNAL(clicked()), QG_MoveOptions, SLOT(changeSelect()));
        QObject::connect(radioButton_fixed, SIGNAL(clicked()), QG_MoveOptions, SLOT(changeSelect()));
        QObject::connect(pushButton_ok, SIGNAL(clicked()), QG_MoveOptions, SLOT(moveFixed()));

        QMetaObject::connectSlotsByName(QG_MoveOptions);
    } // setupUi

    void retranslateUi(QWidget *QG_MoveOptions)
    {
        QG_MoveOptions->setWindowTitle(QApplication::translate("QG_MoveOptions", "Form", 0, QApplication::UnicodeUTF8));
        lbInfo->setText(QApplication::translate("QG_MoveOptions", "\345\271\263\347\247\273\345\217\202\346\225\260:", 0, QApplication::UnicodeUTF8));
        radioButton_manual->setText(QApplication::translate("QG_MoveOptions", "\346\211\213\345\212\250", 0, QApplication::UnicodeUTF8));
        radioButton_fixed->setText(QApplication::translate("QG_MoveOptions", "\345\233\272\345\256\232", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("QG_MoveOptions", "X:", 0, QApplication::UnicodeUTF8));
        lineEdit_xValue->setText(QApplication::translate("QG_MoveOptions", "0", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("QG_MoveOptions", "Y:", 0, QApplication::UnicodeUTF8));
        lineEdit_yValue->setText(QApplication::translate("QG_MoveOptions", "0", 0, QApplication::UnicodeUTF8));
        pushButton_ok->setText(QApplication::translate("QG_MoveOptions", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QG_MoveOptions: public Ui_QG_MoveOptions {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QG_MOVEOPTIONS_H

/********************************************************************************
** Form generated from reading UI file 'qg_lineoptions.ui'
**
** Created: Mon Sep 26 14:56:11 2016
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QG_LINEOPTIONS_H
#define UI_QG_LINEOPTIONS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QG_LineOptions
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_7;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *lineEdit_startX;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *lineEdit_startY;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QLineEdit *lineEdit_endX;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *lineEdit_endY;
    QPushButton *pushButton_next;
    QPushButton *pushButton_ok;

    void setupUi(QWidget *QG_LineOptions)
    {
        if (QG_LineOptions->objectName().isEmpty())
            QG_LineOptions->setObjectName(QString::fromUtf8("QG_LineOptions"));
        QG_LineOptions->resize(458, 26);
        gridLayout = new QGridLayout(QG_LineOptions);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_5 = new QLabel(QG_LineOptions);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_5->addWidget(label_5);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new QLabel(QG_LineOptions);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        lineEdit_startX = new QLineEdit(QG_LineOptions);
        lineEdit_startX->setObjectName(QString::fromUtf8("lineEdit_startX"));

        horizontalLayout->addWidget(lineEdit_startX);


        horizontalLayout_5->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(QG_LineOptions);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        lineEdit_startY = new QLineEdit(QG_LineOptions);
        lineEdit_startY->setObjectName(QString::fromUtf8("lineEdit_startY"));

        horizontalLayout_2->addWidget(lineEdit_startY);


        horizontalLayout_5->addLayout(horizontalLayout_2);


        horizontalLayout_7->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_6 = new QLabel(QG_LineOptions);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_6->addWidget(label_6);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_4 = new QLabel(QG_LineOptions);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_4->addWidget(label_4);

        lineEdit_endX = new QLineEdit(QG_LineOptions);
        lineEdit_endX->setObjectName(QString::fromUtf8("lineEdit_endX"));

        horizontalLayout_4->addWidget(lineEdit_endX);


        horizontalLayout_6->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(QG_LineOptions);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        lineEdit_endY = new QLineEdit(QG_LineOptions);
        lineEdit_endY->setObjectName(QString::fromUtf8("lineEdit_endY"));

        horizontalLayout_3->addWidget(lineEdit_endY);


        horizontalLayout_6->addLayout(horizontalLayout_3);


        horizontalLayout_7->addLayout(horizontalLayout_6);

        pushButton_next = new QPushButton(QG_LineOptions);
        pushButton_next->setObjectName(QString::fromUtf8("pushButton_next"));

        horizontalLayout_7->addWidget(pushButton_next);

        pushButton_ok = new QPushButton(QG_LineOptions);
        pushButton_ok->setObjectName(QString::fromUtf8("pushButton_ok"));

        horizontalLayout_7->addWidget(pushButton_ok);


        gridLayout->addLayout(horizontalLayout_7, 0, 0, 1, 1);


        retranslateUi(QG_LineOptions);
        QObject::connect(pushButton_next, SIGNAL(clicked()), QG_LineOptions, SLOT(slotNext()));
        QObject::connect(pushButton_ok, SIGNAL(clicked()), QG_LineOptions, SLOT(slotOk()));

        QMetaObject::connectSlotsByName(QG_LineOptions);
    } // setupUi

    void retranslateUi(QWidget *QG_LineOptions)
    {
        QG_LineOptions->setWindowTitle(QApplication::translate("QG_LineOptions", "Form", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("QG_LineOptions", "\350\265\267\347\202\271", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("QG_LineOptions", "X:", 0, QApplication::UnicodeUTF8));
        lineEdit_startX->setText(QApplication::translate("QG_LineOptions", "0", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("QG_LineOptions", "Y:", 0, QApplication::UnicodeUTF8));
        lineEdit_startY->setText(QApplication::translate("QG_LineOptions", "0", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("QG_LineOptions", "\347\273\210\347\202\271", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("QG_LineOptions", "X:", 0, QApplication::UnicodeUTF8));
        lineEdit_endX->setText(QApplication::translate("QG_LineOptions", "0", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("QG_LineOptions", "Y:", 0, QApplication::UnicodeUTF8));
        lineEdit_endY->setText(QApplication::translate("QG_LineOptions", "0", 0, QApplication::UnicodeUTF8));
        pushButton_next->setText(QApplication::translate("QG_LineOptions", "\344\270\213\344\270\200\344\270\252", 0, QApplication::UnicodeUTF8));
        pushButton_ok->setText(QApplication::translate("QG_LineOptions", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QG_LineOptions: public Ui_QG_LineOptions {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QG_LINEOPTIONS_H

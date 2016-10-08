/********************************************************************************
** Form generated from reading UI file 'qg_circleoptions.ui'
**
** Created: Mon Sep 26 14:56:11 2016
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QG_CIRCLEOPTIONS_H
#define UI_QG_CIRCLEOPTIONS_H

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

class Ui_QG_CircleOptions
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_7;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *lineEdit_centreX;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *lineEdit_centreY;
    QHBoxLayout *horizontalLayout_6;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QLineEdit *lineEdit_radius;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_next;
    QPushButton *pushButton_ok;

    void setupUi(QWidget *QG_CircleOptions)
    {
        if (QG_CircleOptions->objectName().isEmpty())
            QG_CircleOptions->setObjectName(QString::fromUtf8("QG_CircleOptions"));
        QG_CircleOptions->resize(394, 28);
        gridLayout = new QGridLayout(QG_CircleOptions);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_5 = new QLabel(QG_CircleOptions);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_5->addWidget(label_5);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new QLabel(QG_CircleOptions);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        lineEdit_centreX = new QLineEdit(QG_CircleOptions);
        lineEdit_centreX->setObjectName(QString::fromUtf8("lineEdit_centreX"));

        horizontalLayout->addWidget(lineEdit_centreX);


        horizontalLayout_5->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(QG_CircleOptions);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        lineEdit_centreY = new QLineEdit(QG_CircleOptions);
        lineEdit_centreY->setObjectName(QString::fromUtf8("lineEdit_centreY"));

        horizontalLayout_2->addWidget(lineEdit_centreY);


        horizontalLayout_5->addLayout(horizontalLayout_2);


        horizontalLayout_7->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_4 = new QLabel(QG_CircleOptions);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_4->addWidget(label_4);

        lineEdit_radius = new QLineEdit(QG_CircleOptions);
        lineEdit_radius->setObjectName(QString::fromUtf8("lineEdit_radius"));

        horizontalLayout_4->addWidget(lineEdit_radius);


        horizontalLayout_6->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));

        horizontalLayout_6->addLayout(horizontalLayout_3);


        horizontalLayout_7->addLayout(horizontalLayout_6);

        pushButton_next = new QPushButton(QG_CircleOptions);
        pushButton_next->setObjectName(QString::fromUtf8("pushButton_next"));

        horizontalLayout_7->addWidget(pushButton_next);

        pushButton_ok = new QPushButton(QG_CircleOptions);
        pushButton_ok->setObjectName(QString::fromUtf8("pushButton_ok"));

        horizontalLayout_7->addWidget(pushButton_ok);


        gridLayout->addLayout(horizontalLayout_7, 0, 0, 1, 1);


        retranslateUi(QG_CircleOptions);
        QObject::connect(pushButton_next, SIGNAL(clicked()), QG_CircleOptions, SLOT(slotNext()));
        QObject::connect(pushButton_ok, SIGNAL(clicked()), QG_CircleOptions, SLOT(slotOk()));

        QMetaObject::connectSlotsByName(QG_CircleOptions);
    } // setupUi

    void retranslateUi(QWidget *QG_CircleOptions)
    {
        QG_CircleOptions->setWindowTitle(QApplication::translate("QG_CircleOptions", "Form", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("QG_CircleOptions", "\345\234\206\345\277\203", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("QG_CircleOptions", " X:", 0, QApplication::UnicodeUTF8));
        lineEdit_centreX->setText(QApplication::translate("QG_CircleOptions", "0", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("QG_CircleOptions", " Y:", 0, QApplication::UnicodeUTF8));
        lineEdit_centreY->setText(QApplication::translate("QG_CircleOptions", "0", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("QG_CircleOptions", "\345\215\212\345\276\204", 0, QApplication::UnicodeUTF8));
        lineEdit_radius->setText(QApplication::translate("QG_CircleOptions", "0", 0, QApplication::UnicodeUTF8));
        pushButton_next->setText(QApplication::translate("QG_CircleOptions", "\344\270\213\344\270\200\344\270\252", 0, QApplication::UnicodeUTF8));
        pushButton_ok->setText(QApplication::translate("QG_CircleOptions", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QG_CircleOptions: public Ui_QG_CircleOptions {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QG_CIRCLEOPTIONS_H

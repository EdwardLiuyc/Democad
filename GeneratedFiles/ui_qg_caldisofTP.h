/********************************************************************************
** Form generated from reading UI file 'qg_caldisofTP.ui'
**
** Created: Mon Sep 26 14:56:11 2016
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QG_CALDISOFTP_H
#define UI_QG_CALDISOFTP_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QG_CalDisOfTP
{
public:
    QHBoxLayout *horizontalLayout_9;
    QHBoxLayout *horizontalLayout_8;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *caldisofTP_startX;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *caldisofTP_startY;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QLineEdit *caldisofTP_endX;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *caldisofTP_endY;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_7;
    QLineEdit *caldisofTP_dis;

    void setupUi(QWidget *QG_CalDisOfTP)
    {
        if (QG_CalDisOfTP->objectName().isEmpty())
            QG_CalDisOfTP->setObjectName(QString::fromUtf8("QG_CalDisOfTP"));
        QG_CalDisOfTP->resize(519, 26);
        QG_CalDisOfTP->setMinimumSize(QSize(519, 0));
        horizontalLayout_9 = new QHBoxLayout(QG_CalDisOfTP);
#ifndef Q_OS_MAC
        horizontalLayout_9->setSpacing(6);
#endif
        horizontalLayout_9->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(0);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(-1, -1, -1, 0);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_5 = new QLabel(QG_CalDisOfTP);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_5->addWidget(label_5);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new QLabel(QG_CalDisOfTP);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        caldisofTP_startX = new QLineEdit(QG_CalDisOfTP);
        caldisofTP_startX->setObjectName(QString::fromUtf8("caldisofTP_startX"));

        horizontalLayout->addWidget(caldisofTP_startX);


        horizontalLayout_5->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(QG_CalDisOfTP);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        caldisofTP_startY = new QLineEdit(QG_CalDisOfTP);
        caldisofTP_startY->setObjectName(QString::fromUtf8("caldisofTP_startY"));

        horizontalLayout_2->addWidget(caldisofTP_startY);


        horizontalLayout_5->addLayout(horizontalLayout_2);


        horizontalLayout_8->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_6 = new QLabel(QG_CalDisOfTP);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_6->addWidget(label_6);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_4 = new QLabel(QG_CalDisOfTP);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_4->addWidget(label_4);

        caldisofTP_endX = new QLineEdit(QG_CalDisOfTP);
        caldisofTP_endX->setObjectName(QString::fromUtf8("caldisofTP_endX"));

        horizontalLayout_4->addWidget(caldisofTP_endX);


        horizontalLayout_6->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(QG_CalDisOfTP);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        caldisofTP_endY = new QLineEdit(QG_CalDisOfTP);
        caldisofTP_endY->setObjectName(QString::fromUtf8("caldisofTP_endY"));

        horizontalLayout_3->addWidget(caldisofTP_endY);


        horizontalLayout_6->addLayout(horizontalLayout_3);


        horizontalLayout_8->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_7 = new QLabel(QG_CalDisOfTP);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_7->addWidget(label_7);

        caldisofTP_dis = new QLineEdit(QG_CalDisOfTP);
        caldisofTP_dis->setObjectName(QString::fromUtf8("caldisofTP_dis"));
        caldisofTP_dis->setMinimumSize(QSize(80, 0));

        horizontalLayout_7->addWidget(caldisofTP_dis);


        horizontalLayout_8->addLayout(horizontalLayout_7);


        horizontalLayout_9->addLayout(horizontalLayout_8);


        retranslateUi(QG_CalDisOfTP);

        QMetaObject::connectSlotsByName(QG_CalDisOfTP);
    } // setupUi

    void retranslateUi(QWidget *QG_CalDisOfTP)
    {
        QG_CalDisOfTP->setWindowTitle(QApplication::translate("QG_CalDisOfTP", "Form", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("QG_CalDisOfTP", "\350\265\267\347\202\271", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("QG_CalDisOfTP", "X:", 0, QApplication::UnicodeUTF8));
        caldisofTP_startX->setText(QApplication::translate("QG_CalDisOfTP", "0", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("QG_CalDisOfTP", "Y:", 0, QApplication::UnicodeUTF8));
        caldisofTP_startY->setText(QApplication::translate("QG_CalDisOfTP", "0", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("QG_CalDisOfTP", "\347\273\210\347\202\271", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("QG_CalDisOfTP", "X:", 0, QApplication::UnicodeUTF8));
        caldisofTP_endX->setText(QApplication::translate("QG_CalDisOfTP", "0", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("QG_CalDisOfTP", "Y:", 0, QApplication::UnicodeUTF8));
        caldisofTP_endY->setText(QApplication::translate("QG_CalDisOfTP", "0", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("QG_CalDisOfTP", "\350\267\235\347\246\273", 0, QApplication::UnicodeUTF8));
        caldisofTP_dis->setText(QApplication::translate("QG_CalDisOfTP", "0", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QG_CalDisOfTP: public Ui_QG_CalDisOfTP {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QG_CALDISOFTP_H

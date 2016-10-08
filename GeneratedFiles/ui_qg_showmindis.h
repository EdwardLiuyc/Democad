/********************************************************************************
** Form generated from reading UI file 'qg_showmindis.ui'
**
** Created: Mon Sep 26 14:56:11 2016
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QG_SHOWMINDIS_H
#define UI_QG_SHOWMINDIS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QG_ShowMinDistance
{
public:
    QGridLayout *gridLayout;
    QLabel *label_16;
    QLineEdit *LED_start_x;
    QLabel *label_17;
    QLineEdit *LED_start_y;
    QLabel *label_18;
    QLineEdit *LED_stop_x;
    QLabel *label_19;
    QLineEdit *LED_stop_y;
    QLabel *label_20;
    QLineEdit *LED_Mindistance;

    void setupUi(QWidget *QG_ShowMinDistance)
    {
        if (QG_ShowMinDistance->objectName().isEmpty())
            QG_ShowMinDistance->setObjectName(QString::fromUtf8("QG_ShowMinDistance"));
        QG_ShowMinDistance->resize(519, 20);
        QG_ShowMinDistance->setMinimumSize(QSize(519, 0));
        gridLayout = new QGridLayout(QG_ShowMinDistance);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_16 = new QLabel(QG_ShowMinDistance);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        gridLayout->addWidget(label_16, 0, 0, 1, 1);

        LED_start_x = new QLineEdit(QG_ShowMinDistance);
        LED_start_x->setObjectName(QString::fromUtf8("LED_start_x"));
        LED_start_x->setMaximumSize(QSize(80, 16777215));

        gridLayout->addWidget(LED_start_x, 0, 1, 1, 1);

        label_17 = new QLabel(QG_ShowMinDistance);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        gridLayout->addWidget(label_17, 0, 2, 1, 1);

        LED_start_y = new QLineEdit(QG_ShowMinDistance);
        LED_start_y->setObjectName(QString::fromUtf8("LED_start_y"));
        LED_start_y->setMaximumSize(QSize(80, 16777215));

        gridLayout->addWidget(LED_start_y, 0, 3, 1, 1);

        label_18 = new QLabel(QG_ShowMinDistance);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        gridLayout->addWidget(label_18, 0, 4, 1, 1);

        LED_stop_x = new QLineEdit(QG_ShowMinDistance);
        LED_stop_x->setObjectName(QString::fromUtf8("LED_stop_x"));
        LED_stop_x->setMaximumSize(QSize(80, 16777215));

        gridLayout->addWidget(LED_stop_x, 0, 5, 1, 1);

        label_19 = new QLabel(QG_ShowMinDistance);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        gridLayout->addWidget(label_19, 0, 6, 1, 1);

        LED_stop_y = new QLineEdit(QG_ShowMinDistance);
        LED_stop_y->setObjectName(QString::fromUtf8("LED_stop_y"));
        LED_stop_y->setMaximumSize(QSize(80, 16777215));

        gridLayout->addWidget(LED_stop_y, 0, 7, 1, 1);

        label_20 = new QLabel(QG_ShowMinDistance);
        label_20->setObjectName(QString::fromUtf8("label_20"));

        gridLayout->addWidget(label_20, 0, 8, 1, 1);

        LED_Mindistance = new QLineEdit(QG_ShowMinDistance);
        LED_Mindistance->setObjectName(QString::fromUtf8("LED_Mindistance"));
        LED_Mindistance->setMaximumSize(QSize(80, 16777215));

        gridLayout->addWidget(LED_Mindistance, 0, 9, 1, 1);


        retranslateUi(QG_ShowMinDistance);

        QMetaObject::connectSlotsByName(QG_ShowMinDistance);
    } // setupUi

    void retranslateUi(QWidget *QG_ShowMinDistance)
    {
        QG_ShowMinDistance->setWindowTitle(QApplication::translate("QG_ShowMinDistance", "Form", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("QG_ShowMinDistance", "\350\265\267\347\202\271 x", 0, QApplication::UnicodeUTF8));
        LED_start_x->setText(QApplication::translate("QG_ShowMinDistance", "0", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("QG_ShowMinDistance", "y", 0, QApplication::UnicodeUTF8));
        LED_start_y->setText(QApplication::translate("QG_ShowMinDistance", "0", 0, QApplication::UnicodeUTF8));
        label_18->setText(QApplication::translate("QG_ShowMinDistance", "\347\273\210\347\202\271 x", 0, QApplication::UnicodeUTF8));
        LED_stop_x->setText(QApplication::translate("QG_ShowMinDistance", "0", 0, QApplication::UnicodeUTF8));
        label_19->setText(QApplication::translate("QG_ShowMinDistance", "y", 0, QApplication::UnicodeUTF8));
        LED_stop_y->setText(QApplication::translate("QG_ShowMinDistance", "0", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("QG_ShowMinDistance", "\350\267\235\347\246\273", 0, QApplication::UnicodeUTF8));
        LED_Mindistance->setText(QApplication::translate("QG_ShowMinDistance", "0", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QG_ShowMinDistance: public Ui_QG_ShowMinDistance {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QG_SHOWMINDIS_H

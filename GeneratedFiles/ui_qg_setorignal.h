/********************************************************************************
** Form generated from reading UI file 'qg_setorignal.ui'
**
** Created: Mon Sep 26 14:56:11 2016
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QG_SETORIGNAL_H
#define UI_QG_SETORIGNAL_H

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

class Ui_QG_SetOrignal
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_19;
    QLabel *label_15;
    QHBoxLayout *horizontalLayout_22;
    QLabel *label_16;
    QLineEdit *setOrigin_NewCenterX;
    QHBoxLayout *horizontalLayout_23;
    QLabel *label_17;
    QLineEdit *setOrigin_NewCenterY;
    QPushButton *pushButton_ok;

    void setupUi(QWidget *QG_SetOrignal)
    {
        if (QG_SetOrignal->objectName().isEmpty())
            QG_SetOrignal->setObjectName(QString::fromUtf8("QG_SetOrignal"));
        QG_SetOrignal->resize(519, 24);
        QG_SetOrignal->setMinimumSize(QSize(519, 0));
        gridLayout = new QGridLayout(QG_SetOrignal);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setSpacing(0);
        horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
        label_15 = new QLabel(QG_SetOrignal);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        horizontalLayout_19->addWidget(label_15);

        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setSpacing(0);
        horizontalLayout_22->setObjectName(QString::fromUtf8("horizontalLayout_22"));
        label_16 = new QLabel(QG_SetOrignal);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        horizontalLayout_22->addWidget(label_16);

        setOrigin_NewCenterX = new QLineEdit(QG_SetOrignal);
        setOrigin_NewCenterX->setObjectName(QString::fromUtf8("setOrigin_NewCenterX"));

        horizontalLayout_22->addWidget(setOrigin_NewCenterX);


        horizontalLayout_19->addLayout(horizontalLayout_22);

        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setSpacing(0);
        horizontalLayout_23->setObjectName(QString::fromUtf8("horizontalLayout_23"));
        label_17 = new QLabel(QG_SetOrignal);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        horizontalLayout_23->addWidget(label_17);

        setOrigin_NewCenterY = new QLineEdit(QG_SetOrignal);
        setOrigin_NewCenterY->setObjectName(QString::fromUtf8("setOrigin_NewCenterY"));

        horizontalLayout_23->addWidget(setOrigin_NewCenterY);


        horizontalLayout_19->addLayout(horizontalLayout_23);


        gridLayout->addLayout(horizontalLayout_19, 0, 0, 1, 1);

        pushButton_ok = new QPushButton(QG_SetOrignal);
        pushButton_ok->setObjectName(QString::fromUtf8("pushButton_ok"));

        gridLayout->addWidget(pushButton_ok, 0, 1, 1, 1);


        retranslateUi(QG_SetOrignal);

        QMetaObject::connectSlotsByName(QG_SetOrignal);
    } // setupUi

    void retranslateUi(QWidget *QG_SetOrignal)
    {
        QG_SetOrignal->setWindowTitle(QApplication::translate("QG_SetOrignal", "Form", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("QG_SetOrignal", "\346\226\260\347\232\204\345\216\237\347\202\271", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("QG_SetOrignal", "X:", 0, QApplication::UnicodeUTF8));
        setOrigin_NewCenterX->setText(QApplication::translate("QG_SetOrignal", "0", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("QG_SetOrignal", "Y:", 0, QApplication::UnicodeUTF8));
        setOrigin_NewCenterY->setText(QApplication::translate("QG_SetOrignal", "0", 0, QApplication::UnicodeUTF8));
        pushButton_ok->setText(QApplication::translate("QG_SetOrignal", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QG_SetOrignal: public Ui_QG_SetOrignal {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QG_SETORIGNAL_H

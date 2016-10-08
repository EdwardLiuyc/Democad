/********************************************************************************
** Form generated from reading UI file 'qg_setgridtype.ui'
**
** Created: Mon Sep 26 14:56:11 2016
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QG_SETGRIDTYPE_H
#define UI_QG_SETGRIDTYPE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QG_SetGridType
{
public:
    QPushButton *pushButton_ok;
    QLabel *lbGap;
    QLineEdit *setGridGap;
    QLabel *lbInfo;
    QComboBox *CMB_setGridType;

    void setupUi(QWidget *QG_SetGridType)
    {
        if (QG_SetGridType->objectName().isEmpty())
            QG_SetGridType->setObjectName(QString::fromUtf8("QG_SetGridType"));
        QG_SetGridType->resize(438, 37);
        QG_SetGridType->setMinimumSize(QSize(0, 0));
        pushButton_ok = new QPushButton(QG_SetGridType);
        pushButton_ok->setObjectName(QString::fromUtf8("pushButton_ok"));
        pushButton_ok->setGeometry(QRect(319, 6, 61, 23));
        QFont font;
        font.setPointSize(12);
        pushButton_ok->setFont(font);
        lbGap = new QLabel(QG_SetGridType);
        lbGap->setObjectName(QString::fromUtf8("lbGap"));
        lbGap->setGeometry(QRect(212, 7, 38, 20));
        lbGap->setFont(font);
        setGridGap = new QLineEdit(QG_SetGridType);
        setGridGap->setObjectName(QString::fromUtf8("setGridGap"));
        setGridGap->setGeometry(QRect(255, 7, 51, 20));
        setGridGap->setMaximumSize(QSize(80, 16777215));
        setGridGap->setFont(font);
        setGridGap->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lbInfo = new QLabel(QG_SetGridType);
        lbInfo->setObjectName(QString::fromUtf8("lbInfo"));
        lbInfo->setGeometry(QRect(7, 7, 125, 20));
        lbInfo->setFont(font);
        CMB_setGridType = new QComboBox(QG_SetGridType);
        CMB_setGridType->setObjectName(QString::fromUtf8("CMB_setGridType"));
        CMB_setGridType->setGeometry(QRect(135, 7, 65, 20));
        CMB_setGridType->setFont(font);

        retranslateUi(QG_SetGridType);

        QMetaObject::connectSlotsByName(QG_SetGridType);
    } // setupUi

    void retranslateUi(QWidget *QG_SetGridType)
    {
        QG_SetGridType->setWindowTitle(QApplication::translate("QG_SetGridType", "Form", 0, QApplication::UnicodeUTF8));
        pushButton_ok->setText(QApplication::translate("QG_SetGridType", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        lbGap->setText(QApplication::translate("QG_SetGridType", "\351\227\264\351\232\224", 0, QApplication::UnicodeUTF8));
        setGridGap->setText(QApplication::translate("QG_SetGridType", " 10", 0, QApplication::UnicodeUTF8));
        lbInfo->setText(QApplication::translate("QG_SetGridType", "\347\275\221\346\240\274\345\217\202\346\225\260:  \347\261\273\345\236\213", 0, QApplication::UnicodeUTF8));
        CMB_setGridType->clear();
        CMB_setGridType->insertItems(0, QStringList()
         << QApplication::translate("QG_SetGridType", " \350\231\232\347\272\277", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QG_SetGridType", " \345\256\236\347\272\277", 0, QApplication::UnicodeUTF8)
        );
    } // retranslateUi

};

namespace Ui {
    class QG_SetGridType: public Ui_QG_SetGridType {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QG_SETGRIDTYPE_H

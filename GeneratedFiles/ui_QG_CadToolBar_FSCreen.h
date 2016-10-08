/********************************************************************************
** Form generated from reading UI file 'QG_CadToolBar_FSCreen.ui'
**
** Created: Mon Sep 26 14:56:11 2016
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QG_CADTOOLBAR_FSCREEN_H
#define UI_QG_CADTOOLBAR_FSCREEN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QToolButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QG_CadToolBar_FSCreen
{
public:
    QToolButton *btnFSCreen;

    void setupUi(QWidget *QG_CadToolBar_FSCreen)
    {
        if (QG_CadToolBar_FSCreen->objectName().isEmpty())
            QG_CadToolBar_FSCreen->setObjectName(QString::fromUtf8("QG_CadToolBar_FSCreen"));
        QG_CadToolBar_FSCreen->resize(84, 40);
        btnFSCreen = new QToolButton(QG_CadToolBar_FSCreen);
        btnFSCreen->setObjectName(QString::fromUtf8("btnFSCreen"));
        btnFSCreen->setGeometry(QRect(2, 2, 36, 36));
        btnFSCreen->setMaximumSize(QSize(36, 36));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/extui/FullScreen.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon.addFile(QString::fromUtf8(":/extui/quitFullScreen.png"), QSize(), QIcon::Normal, QIcon::On);
        icon.addFile(QString::fromUtf8(":/extui/FullScreen.png"), QSize(), QIcon::Disabled, QIcon::Off);
        icon.addFile(QString::fromUtf8(":/extui/quitFullScreen.png"), QSize(), QIcon::Disabled, QIcon::On);
        icon.addFile(QString::fromUtf8(":/extui/FullScreen.png"), QSize(), QIcon::Active, QIcon::Off);
        icon.addFile(QString::fromUtf8(":/extui/quitFullScreen.png"), QSize(), QIcon::Active, QIcon::On);
        icon.addFile(QString::fromUtf8(":/extui/FullScreen.png"), QSize(), QIcon::Selected, QIcon::Off);
        icon.addFile(QString::fromUtf8(":/extui/quitFullScreen.png"), QSize(), QIcon::Selected, QIcon::On);
        btnFSCreen->setIcon(icon);
        btnFSCreen->setIconSize(QSize(32, 32));
        btnFSCreen->setCheckable(true);
        btnFSCreen->setAutoExclusive(true);

        retranslateUi(QG_CadToolBar_FSCreen);

        QMetaObject::connectSlotsByName(QG_CadToolBar_FSCreen);
    } // setupUi

    void retranslateUi(QWidget *QG_CadToolBar_FSCreen)
    {
        QG_CadToolBar_FSCreen->setWindowTitle(QApplication::translate("QG_CadToolBar_FSCreen", "QG_CadToolBar_FSCreen", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        btnFSCreen->setToolTip(QApplication::translate("QG_CadToolBar_FSCreen", "\345\205\250\345\261\217", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btnFSCreen->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class QG_CadToolBar_FSCreen: public Ui_QG_CadToolBar_FSCreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QG_CADTOOLBAR_FSCREEN_H

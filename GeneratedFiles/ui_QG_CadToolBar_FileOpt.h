/********************************************************************************
** Form generated from reading UI file 'QG_CadToolBar_FileOpt.ui'
**
** Created: Mon Sep 26 14:56:11 2016
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QG_CADTOOLBAR_FILEOPT_H
#define UI_QG_CADTOOLBAR_FILEOPT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QToolButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QG_CadToolBar_FileOpt
{
public:
    QToolButton *btnNew;
    QToolButton *btnOpen;
    QToolButton *btnSave;
    QToolButton *btnSaveAs;
    QFrame *line;
    QLabel *LeadPara;

    void setupUi(QWidget *QG_CadToolBar_FileOpt)
    {
        if (QG_CadToolBar_FileOpt->objectName().isEmpty())
            QG_CadToolBar_FileOpt->setObjectName(QString::fromUtf8("QG_CadToolBar_FileOpt"));
        QG_CadToolBar_FileOpt->resize(96, 107);
        btnNew = new QToolButton(QG_CadToolBar_FileOpt);
        btnNew->setObjectName(QString::fromUtf8("btnNew"));
        btnNew->setGeometry(QRect(32, 29, 32, 32));
        btnNew->setMaximumSize(QSize(32, 32));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/extui/new.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon.addFile(QString::fromUtf8(":/extui/new_ON.png"), QSize(), QIcon::Normal, QIcon::On);
        icon.addFile(QString::fromUtf8(":/extui/new.png"), QSize(), QIcon::Disabled, QIcon::Off);
        icon.addFile(QString::fromUtf8(":/extui/new_ON.png"), QSize(), QIcon::Disabled, QIcon::On);
        icon.addFile(QString::fromUtf8(":/extui/new.png"), QSize(), QIcon::Active, QIcon::Off);
        icon.addFile(QString::fromUtf8(":/extui/new_ON.png"), QSize(), QIcon::Active, QIcon::On);
        icon.addFile(QString::fromUtf8(":/extui/new.png"), QSize(), QIcon::Selected, QIcon::Off);
        icon.addFile(QString::fromUtf8(":/extui/new_ON.png"), QSize(), QIcon::Selected, QIcon::On);
        btnNew->setIcon(icon);
        btnNew->setIconSize(QSize(32, 32));
        btnNew->setCheckable(true);
        btnNew->setAutoExclusive(false);
        btnOpen = new QToolButton(QG_CadToolBar_FileOpt);
        btnOpen->setObjectName(QString::fromUtf8("btnOpen"));
        btnOpen->setGeometry(QRect(1, 29, 32, 32));
        btnOpen->setMaximumSize(QSize(32, 32));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/extui/fileopen.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon1.addFile(QString::fromUtf8(":/extui/fileopen_ON.png"), QSize(), QIcon::Normal, QIcon::On);
        icon1.addFile(QString::fromUtf8(":/extui/fileopen.png"), QSize(), QIcon::Disabled, QIcon::Off);
        icon1.addFile(QString::fromUtf8(":/extui/fileopen_ON.png"), QSize(), QIcon::Disabled, QIcon::On);
        icon1.addFile(QString::fromUtf8(":/extui/fileopen.png"), QSize(), QIcon::Active, QIcon::Off);
        icon1.addFile(QString::fromUtf8(":/extui/fileopen_ON.png"), QSize(), QIcon::Active, QIcon::On);
        icon1.addFile(QString::fromUtf8(":/extui/fileopen.png"), QSize(), QIcon::Selected, QIcon::Off);
        icon1.addFile(QString::fromUtf8(":/extui/fileopen_ON.png"), QSize(), QIcon::Selected, QIcon::On);
        btnOpen->setIcon(icon1);
        btnOpen->setIconSize(QSize(32, 32));
        btnOpen->setCheckable(true);
        btnOpen->setAutoExclusive(false);
        btnSave = new QToolButton(QG_CadToolBar_FileOpt);
        btnSave->setObjectName(QString::fromUtf8("btnSave"));
        btnSave->setGeometry(QRect(1, 60, 32, 32));
        btnSave->setMaximumSize(QSize(32, 32));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/extui/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon2.addFile(QString::fromUtf8(":/extui/save_ON.png"), QSize(), QIcon::Normal, QIcon::On);
        icon2.addFile(QString::fromUtf8(":/extui/save.png"), QSize(), QIcon::Disabled, QIcon::Off);
        icon2.addFile(QString::fromUtf8(":/extui/save_ON.png"), QSize(), QIcon::Disabled, QIcon::On);
        icon2.addFile(QString::fromUtf8(":/extui/save.png"), QSize(), QIcon::Active, QIcon::Off);
        icon2.addFile(QString::fromUtf8(":/extui/save_ON.png"), QSize(), QIcon::Active, QIcon::On);
        icon2.addFile(QString::fromUtf8(":/extui/save.png"), QSize(), QIcon::Selected, QIcon::Off);
        icon2.addFile(QString::fromUtf8(":/extui/save_ON.png"), QSize(), QIcon::Selected, QIcon::On);
        btnSave->setIcon(icon2);
        btnSave->setIconSize(QSize(32, 32));
        btnSave->setCheckable(true);
        btnSave->setAutoExclusive(false);
        btnSaveAs = new QToolButton(QG_CadToolBar_FileOpt);
        btnSaveAs->setObjectName(QString::fromUtf8("btnSaveAs"));
        btnSaveAs->setGeometry(QRect(32, 60, 32, 32));
        btnSaveAs->setMaximumSize(QSize(32, 32));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/extui/saveas.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon3.addFile(QString::fromUtf8(":/extui/saveas_ON.png"), QSize(), QIcon::Normal, QIcon::On);
        icon3.addFile(QString::fromUtf8(":/extui/saveas.png"), QSize(), QIcon::Disabled, QIcon::Off);
        icon3.addFile(QString::fromUtf8(":/extui/saveas_ON.png"), QSize(), QIcon::Disabled, QIcon::On);
        icon3.addFile(QString::fromUtf8(":/extui/saveas.png"), QSize(), QIcon::Active, QIcon::Off);
        icon3.addFile(QString::fromUtf8(":/extui/saveas_ON.png"), QSize(), QIcon::Active, QIcon::On);
        icon3.addFile(QString::fromUtf8(":/extui/saveas.png"), QSize(), QIcon::Selected, QIcon::Off);
        icon3.addFile(QString::fromUtf8(":/extui/saveas_ON.png"), QSize(), QIcon::Selected, QIcon::On);
        btnSaveAs->setIcon(icon3);
        btnSaveAs->setIconSize(QSize(32, 32));
        btnSaveAs->setCheckable(true);
        btnSaveAs->setAutoExclusive(false);
        line = new QFrame(QG_CadToolBar_FileOpt);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(0, 1, 80, 3));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        LeadPara = new QLabel(QG_CadToolBar_FileOpt);
        LeadPara->setObjectName(QString::fromUtf8("LeadPara"));
        LeadPara->setGeometry(QRect(3, 10, 61, 16));
        QFont font;
        font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font.setPointSize(10);
        LeadPara->setFont(font);
        LeadPara->setAlignment(Qt::AlignCenter);

        retranslateUi(QG_CadToolBar_FileOpt);

        QMetaObject::connectSlotsByName(QG_CadToolBar_FileOpt);
    } // setupUi

    void retranslateUi(QWidget *QG_CadToolBar_FileOpt)
    {
        QG_CadToolBar_FileOpt->setWindowTitle(QApplication::translate("QG_CadToolBar_FileOpt", "QG_CadToolBar_FileOpt", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        btnNew->setToolTip(QApplication::translate("QG_CadToolBar_FileOpt", "\346\226\260\345\273\272", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btnNew->setText(QString());
#ifndef QT_NO_TOOLTIP
        btnOpen->setToolTip(QApplication::translate("QG_CadToolBar_FileOpt", "\346\211\223\345\274\200", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btnOpen->setText(QString());
#ifndef QT_NO_TOOLTIP
        btnSave->setToolTip(QApplication::translate("QG_CadToolBar_FileOpt", "\344\277\235\345\255\230", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btnSave->setText(QString());
#ifndef QT_NO_TOOLTIP
        btnSaveAs->setToolTip(QApplication::translate("QG_CadToolBar_FileOpt", "\345\217\246\345\255\230\344\270\272DXF", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btnSaveAs->setText(QString());
        LeadPara->setText(QApplication::translate("QG_CadToolBar_FileOpt", "\346\226\207\344\273\266\346\223\215\344\275\234", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QG_CadToolBar_FileOpt: public Ui_QG_CadToolBar_FileOpt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QG_CADTOOLBAR_FILEOPT_H

/********************************************************************************
** Form generated from reading UI file 'QG_CadToolBar_LeadWire.ui'
**
** Created: Mon Sep 26 14:56:11 2016
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QG_CADTOOLBAR_LEADWIRE_H
#define UI_QG_CADTOOLBAR_LEADWIRE_H

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

class Ui_QG_CadToolBar_LeadWire
{
public:
    QToolButton *btnPoint;
    QLabel *LeadPara;
    QToolButton *btnVertical;
    QToolButton *btnAngle1;
    QToolButton *btnAngle2;
    QFrame *line;

    void setupUi(QWidget *QG_CadToolBar_LeadWire)
    {
        if (QG_CadToolBar_LeadWire->objectName().isEmpty())
            QG_CadToolBar_LeadWire->setObjectName(QString::fromUtf8("QG_CadToolBar_LeadWire"));
        QG_CadToolBar_LeadWire->resize(96, 98);
        btnPoint = new QToolButton(QG_CadToolBar_LeadWire);
        btnPoint->setObjectName(QString::fromUtf8("btnPoint"));
        btnPoint->setEnabled(true);
        btnPoint->setGeometry(QRect(32, 29, 32, 32));
        btnPoint->setMaximumSize(QSize(32, 32));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/extui/linesangle_OFF.png"), QSize(), QIcon::Active, QIcon::Off);
        icon.addFile(QString::fromUtf8(":/extui/linesangle_ON.png"), QSize(), QIcon::Active, QIcon::On);
        btnPoint->setIcon(icon);
        btnPoint->setIconSize(QSize(32, 32));
        btnPoint->setCheckable(true);
        btnPoint->setAutoExclusive(false);
        LeadPara = new QLabel(QG_CadToolBar_LeadWire);
        LeadPara->setObjectName(QString::fromUtf8("LeadPara"));
        LeadPara->setGeometry(QRect(3, 12, 61, 16));
        QFont font;
        font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font.setPointSize(10);
        LeadPara->setFont(font);
        LeadPara->setAlignment(Qt::AlignCenter);
        btnVertical = new QToolButton(QG_CadToolBar_LeadWire);
        btnVertical->setObjectName(QString::fromUtf8("btnVertical"));
        btnVertical->setGeometry(QRect(1, 29, 32, 32));
        btnVertical->setMaximumSize(QSize(32, 32));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/extui/linesver_OFF.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon1.addFile(QString::fromUtf8(":/extui/linesver_OFF.png"), QSize(), QIcon::Active, QIcon::Off);
        icon1.addFile(QString::fromUtf8(":/extui/linesver_ON.png"), QSize(), QIcon::Active, QIcon::On);
        btnVertical->setIcon(icon1);
        btnVertical->setIconSize(QSize(32, 32));
        btnVertical->setCheckable(true);
        btnVertical->setAutoExclusive(false);
        btnAngle1 = new QToolButton(QG_CadToolBar_LeadWire);
        btnAngle1->setObjectName(QString::fromUtf8("btnAngle1"));
        btnAngle1->setEnabled(true);
        btnAngle1->setGeometry(QRect(1, 60, 32, 32));
        btnAngle1->setMaximumSize(QSize(32, 32));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/extui/linestan1_OFF.png"), QSize(), QIcon::Active, QIcon::Off);
        icon2.addFile(QString::fromUtf8(":/extui/linestan1_ON.png"), QSize(), QIcon::Active, QIcon::On);
        btnAngle1->setIcon(icon2);
        btnAngle1->setIconSize(QSize(32, 32));
        btnAngle1->setCheckable(true);
        btnAngle1->setAutoExclusive(false);
        btnAngle2 = new QToolButton(QG_CadToolBar_LeadWire);
        btnAngle2->setObjectName(QString::fromUtf8("btnAngle2"));
        btnAngle2->setEnabled(true);
        btnAngle2->setGeometry(QRect(32, 60, 32, 32));
        btnAngle2->setMaximumSize(QSize(32, 32));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/extui/linesorthogonal_OFF.png"), QSize(), QIcon::Active, QIcon::Off);
        icon3.addFile(QString::fromUtf8(":/extui/linesorthogonal_ON.png"), QSize(), QIcon::Active, QIcon::On);
        btnAngle2->setIcon(icon3);
        btnAngle2->setIconSize(QSize(32, 32));
        btnAngle2->setCheckable(true);
        btnAngle2->setAutoExclusive(false);
        line = new QFrame(QG_CadToolBar_LeadWire);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(0, 1, 80, 3));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        retranslateUi(QG_CadToolBar_LeadWire);

        QMetaObject::connectSlotsByName(QG_CadToolBar_LeadWire);
    } // setupUi

    void retranslateUi(QWidget *QG_CadToolBar_LeadWire)
    {
        QG_CadToolBar_LeadWire->setWindowTitle(QApplication::translate("QG_CadToolBar_LeadWire", "QG_CadToolBar_LeadWire", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        btnPoint->setToolTip(QApplication::translate("QG_CadToolBar_LeadWire", "\347\253\257\347\202\271", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btnPoint->setText(QString());
        LeadPara->setText(QApplication::translate("QG_CadToolBar_LeadWire", "\345\274\225\347\272\277\350\256\276\345\256\232", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        btnVertical->setToolTip(QApplication::translate("QG_CadToolBar_LeadWire", "\347\233\264\347\272\277", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btnVertical->setText(QString());
#ifndef QT_NO_TOOLTIP
        btnAngle1->setToolTip(QApplication::translate("QG_CadToolBar_LeadWire", "\345\234\206\345\274\2471", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btnAngle1->setText(QString());
#ifndef QT_NO_TOOLTIP
        btnAngle2->setToolTip(QApplication::translate("QG_CadToolBar_LeadWire", "\345\234\206\345\274\2472", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btnAngle2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class QG_CadToolBar_LeadWire: public Ui_QG_CadToolBar_LeadWire {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QG_CADTOOLBAR_LEADWIRE_H

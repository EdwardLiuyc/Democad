/********************************************************************************
** Form generated from reading UI file 'QG_CadToolBar_AssistTool.ui'
**
** Created: Mon Sep 26 14:56:11 2016
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QG_CADTOOLBAR_ASSISTTOOL_H
#define UI_QG_CADTOOLBAR_ASSISTTOOL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QToolButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QG_CadToolBar_AssistTool
{
public:
    QToolButton *btnAngle;
    QToolButton *btnSizeSet;
    QToolButton *btnPointDistance;
    QToolButton *btnFullScreen;
    QToolButton *btnOriginalSet;
    QToolButton *btnOriginalInit;
    QToolButton *btnShowValue;
    QToolButton *bHidden;
    QToolButton *btnGridSet;
    QToolButton *btnCellDistance;
    QFrame *line_2;

    void setupUi(QWidget *QG_CadToolBar_AssistTool)
    {
        if (QG_CadToolBar_AssistTool->objectName().isEmpty())
            QG_CadToolBar_AssistTool->setObjectName(QString::fromUtf8("QG_CadToolBar_AssistTool"));
        QG_CadToolBar_AssistTool->resize(80, 200);
        btnAngle = new QToolButton(QG_CadToolBar_AssistTool);
        btnAngle->setObjectName(QString::fromUtf8("btnAngle"));
        btnAngle->setGeometry(QRect(32, 32, 32, 32));
        btnAngle->setMaximumSize(QSize(32, 32));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/extui/Angle.png"), QSize(), QIcon::Active, QIcon::Off);
        icon.addFile(QString::fromUtf8(":/extui/Angle_ON.png"), QSize(), QIcon::Active, QIcon::On);
        btnAngle->setIcon(icon);
        btnAngle->setIconSize(QSize(32, 32));
        btnAngle->setCheckable(true);
        btnAngle->setChecked(false);
        btnAngle->setAutoExclusive(false);
        btnSizeSet = new QToolButton(QG_CadToolBar_AssistTool);
        btnSizeSet->setObjectName(QString::fromUtf8("btnSizeSet"));
        btnSizeSet->setGeometry(QRect(32, 105, 32, 32));
        btnSizeSet->setMaximumSize(QSize(32, 32));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/extui/SizeSet.png"), QSize(), QIcon::Active, QIcon::Off);
        icon1.addFile(QString::fromUtf8(":/extui/SizeSet_ON.png"), QSize(), QIcon::Active, QIcon::On);
        btnSizeSet->setIcon(icon1);
        btnSizeSet->setIconSize(QSize(32, 32));
        btnSizeSet->setCheckable(true);
        btnSizeSet->setAutoRepeat(false);
        btnSizeSet->setAutoExclusive(false);
        btnPointDistance = new QToolButton(QG_CadToolBar_AssistTool);
        btnPointDistance->setObjectName(QString::fromUtf8("btnPointDistance"));
        btnPointDistance->setGeometry(QRect(32, 1, 32, 32));
        btnPointDistance->setMaximumSize(QSize(32, 32));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/extui/PointD.png"), QSize(), QIcon::Active, QIcon::Off);
        icon2.addFile(QString::fromUtf8(":/extui/PointD_ON.png"), QSize(), QIcon::Active, QIcon::On);
        btnPointDistance->setIcon(icon2);
        btnPointDistance->setIconSize(QSize(32, 32));
        btnPointDistance->setCheckable(true);
        btnPointDistance->setChecked(false);
        btnPointDistance->setAutoExclusive(false);
        btnFullScreen = new QToolButton(QG_CadToolBar_AssistTool);
        btnFullScreen->setObjectName(QString::fromUtf8("btnFullScreen"));
        btnFullScreen->setGeometry(QRect(1, 63, 32, 32));
        btnFullScreen->setMaximumSize(QSize(32, 32));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/extui/gfs.png"), QSize(), QIcon::Active, QIcon::Off);
        icon3.addFile(QString::fromUtf8(":/extui/gfs_ON.png"), QSize(), QIcon::Active, QIcon::On);
        btnFullScreen->setIcon(icon3);
        btnFullScreen->setIconSize(QSize(32, 32));
        btnFullScreen->setCheckable(true);
        btnFullScreen->setChecked(false);
        btnFullScreen->setAutoExclusive(false);
        btnOriginalSet = new QToolButton(QG_CadToolBar_AssistTool);
        btnOriginalSet->setObjectName(QString::fromUtf8("btnOriginalSet"));
        btnOriginalSet->setGeometry(QRect(1, 136, 32, 32));
        btnOriginalSet->setMaximumSize(QSize(32, 32));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/extui/OriSet.png"), QSize(), QIcon::Active, QIcon::Off);
        icon4.addFile(QString::fromUtf8(":/extui/OriSet_ON.png"), QSize(), QIcon::Active, QIcon::On);
        btnOriginalSet->setIcon(icon4);
        btnOriginalSet->setIconSize(QSize(32, 32));
        btnOriginalSet->setCheckable(true);
        btnOriginalSet->setAutoRepeat(false);
        btnOriginalSet->setAutoExclusive(false);
        btnOriginalInit = new QToolButton(QG_CadToolBar_AssistTool);
        btnOriginalInit->setObjectName(QString::fromUtf8("btnOriginalInit"));
        btnOriginalInit->setGeometry(QRect(32, 136, 32, 32));
        btnOriginalInit->setMaximumSize(QSize(32, 32));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/extui/OriginalInit.png"), QSize(), QIcon::Active, QIcon::Off);
        icon5.addFile(QString::fromUtf8(":/extui/OriginalInit_ON.png"), QSize(), QIcon::Active, QIcon::On);
        btnOriginalInit->setIcon(icon5);
        btnOriginalInit->setIconSize(QSize(32, 32));
        btnOriginalInit->setCheckable(true);
        btnOriginalInit->setAutoRepeat(false);
        btnOriginalInit->setAutoExclusive(false);
        btnOriginalInit->setAutoRepeatDelay(500);
        btnShowValue = new QToolButton(QG_CadToolBar_AssistTool);
        btnShowValue->setObjectName(QString::fromUtf8("btnShowValue"));
        btnShowValue->setGeometry(QRect(1, 1, 32, 32));
        btnShowValue->setMaximumSize(QSize(32, 32));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/extui/ShowV.png"), QSize(), QIcon::Active, QIcon::Off);
        icon6.addFile(QString::fromUtf8(":/extui/ShowV_ON.png"), QSize(), QIcon::Active, QIcon::On);
        btnShowValue->setIcon(icon6);
        btnShowValue->setIconSize(QSize(32, 32));
        btnShowValue->setCheckable(true);
        btnShowValue->setChecked(false);
        btnShowValue->setAutoExclusive(false);
        bHidden = new QToolButton(QG_CadToolBar_AssistTool);
        bHidden->setObjectName(QString::fromUtf8("bHidden"));
        bHidden->setGeometry(QRect(1, 280, 0, 0));
        bHidden->setMaximumSize(QSize(0, 0));
        bHidden->setIconSize(QSize(0, 0));
        bHidden->setCheckable(true);
        bHidden->setAutoExclusive(true);
        btnGridSet = new QToolButton(QG_CadToolBar_AssistTool);
        btnGridSet->setObjectName(QString::fromUtf8("btnGridSet"));
        btnGridSet->setGeometry(QRect(1, 105, 32, 32));
        btnGridSet->setMaximumSize(QSize(32, 32));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/extui/GridSet.png"), QSize(), QIcon::Active, QIcon::Off);
        icon7.addFile(QString::fromUtf8(":/extui/GridSet_ON.png"), QSize(), QIcon::Active, QIcon::On);
        btnGridSet->setIcon(icon7);
        btnGridSet->setIconSize(QSize(32, 32));
        btnGridSet->setCheckable(true);
        btnGridSet->setAutoRepeat(false);
        btnGridSet->setAutoExclusive(false);
        btnCellDistance = new QToolButton(QG_CadToolBar_AssistTool);
        btnCellDistance->setObjectName(QString::fromUtf8("btnCellDistance"));
        btnCellDistance->setGeometry(QRect(1, 32, 32, 32));
        btnCellDistance->setMaximumSize(QSize(32, 32));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/extui/ElementD.png"), QSize(), QIcon::Active, QIcon::Off);
        icon8.addFile(QString::fromUtf8(":/extui/ElementD_ON.png"), QSize(), QIcon::Active, QIcon::On);
        btnCellDistance->setIcon(icon8);
        btnCellDistance->setIconSize(QSize(32, 32));
        btnCellDistance->setCheckable(true);
        btnCellDistance->setChecked(false);
        btnCellDistance->setAutoExclusive(false);
        line_2 = new QFrame(QG_CadToolBar_AssistTool);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(1, 92, 65, 16));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        retranslateUi(QG_CadToolBar_AssistTool);

        QMetaObject::connectSlotsByName(QG_CadToolBar_AssistTool);
    } // setupUi

    void retranslateUi(QWidget *QG_CadToolBar_AssistTool)
    {
        QG_CadToolBar_AssistTool->setWindowTitle(QApplication::translate("QG_CadToolBar_AssistTool", "QG_CadToolBar_AssistTool", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        btnAngle->setToolTip(QApplication::translate("QG_CadToolBar_AssistTool", "\350\247\222\345\272\246", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btnAngle->setText(QString());
#ifndef QT_NO_TOOLTIP
        btnSizeSet->setToolTip(QApplication::translate("QG_CadToolBar_AssistTool", "\345\260\272\345\257\270\345\210\235\345\247\213\345\214\226", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btnSizeSet->setText(QString());
#ifndef QT_NO_TOOLTIP
        btnPointDistance->setToolTip(QApplication::translate("QG_CadToolBar_AssistTool", "\344\270\244\347\202\271\351\227\264\350\267\235\347\246\273", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btnPointDistance->setText(QString());
#ifndef QT_NO_TOOLTIP
        btnFullScreen->setToolTip(QApplication::translate("QG_CadToolBar_AssistTool", "\346\273\241\345\261\217", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btnFullScreen->setText(QString());
#ifndef QT_NO_TOOLTIP
        btnOriginalSet->setToolTip(QApplication::translate("QG_CadToolBar_AssistTool", "\345\216\237\347\202\271\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btnOriginalSet->setText(QString());
#ifndef QT_NO_TOOLTIP
        btnOriginalInit->setToolTip(QApplication::translate("QG_CadToolBar_AssistTool", "\345\216\237\347\202\271\345\210\235\345\247\213\345\214\226", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btnOriginalInit->setText(QString());
#ifndef QT_NO_TOOLTIP
        btnShowValue->setToolTip(QApplication::translate("QG_CadToolBar_AssistTool", "\346\230\276\345\200\274", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btnShowValue->setText(QString());
#ifndef QT_NO_TOOLTIP
        bHidden->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        bHidden->setText(QString());
#ifndef QT_NO_TOOLTIP
        btnGridSet->setToolTip(QApplication::translate("QG_CadToolBar_AssistTool", "\346\240\205\346\240\274\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btnGridSet->setText(QString());
#ifndef QT_NO_TOOLTIP
        btnCellDistance->setToolTip(QApplication::translate("QG_CadToolBar_AssistTool", "\350\246\201\347\264\240\351\227\264\350\267\235\347\246\273", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btnCellDistance->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class QG_CadToolBar_AssistTool: public Ui_QG_CadToolBar_AssistTool {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QG_CADTOOLBAR_ASSISTTOOL_H

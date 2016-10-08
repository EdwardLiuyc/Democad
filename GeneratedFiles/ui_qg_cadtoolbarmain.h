/********************************************************************************
** Form generated from reading UI file 'qg_cadtoolbarmain.ui'
**
** Created: Mon Sep 26 14:56:11 2016
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QG_CADTOOLBARMAIN_H
#define UI_QG_CADTOOLBARMAIN_H

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

class Ui_QG_CadToolBarMain
{
public:
    QToolButton *bHidden;
    QToolButton *bTrim;
    QToolButton *bTrim2;
    QToolButton *bScale;
    QToolButton *bMove;
    QToolButton *bRotate;
    QToolButton *bMirror;
    QFrame *line;
    QFrame *line_2;
    QToolButton *bCircle;
    QToolButton *bNormal;
    QToolButton *bRectangle;
    QToolButton *bArc;
    QFrame *line_3;
    QToolButton *bDel;
    QToolButton *bUnAll;
    QToolButton *bAll;
    QToolButton *bInvert;
    QLabel *lCoord1;
    QLabel *lCoord1b;
    QLabel *lGridGap;

    void setupUi(QWidget *QG_CadToolBarMain)
    {
        if (QG_CadToolBarMain->objectName().isEmpty())
            QG_CadToolBarMain->setObjectName(QString::fromUtf8("QG_CadToolBarMain"));
        QG_CadToolBarMain->resize(80, 307);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QG_CadToolBarMain->sizePolicy().hasHeightForWidth());
        QG_CadToolBarMain->setSizePolicy(sizePolicy);
        QG_CadToolBarMain->setMinimumSize(QSize(0, 0));
        QG_CadToolBarMain->setMaximumSize(QSize(80, 457));
        bHidden = new QToolButton(QG_CadToolBarMain);
        bHidden->setObjectName(QString::fromUtf8("bHidden"));
        bHidden->setGeometry(QRect(2, 353, 0, 0));
        bHidden->setMaximumSize(QSize(0, 0));
        bHidden->setIconSize(QSize(0, 0));
        bHidden->setCheckable(true);
        bHidden->setAutoExclusive(true);
        bTrim = new QToolButton(QG_CadToolBarMain);
        bTrim->setObjectName(QString::fromUtf8("bTrim"));
        bTrim->setEnabled(true);
        bTrim->setGeometry(QRect(2, 70, 32, 32));
        bTrim->setMaximumSize(QSize(32, 32));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/extui/modifytrim_OFF.png"), QSize(), QIcon::Active, QIcon::Off);
        icon.addFile(QString::fromUtf8(":/extui/modifytrim_ON.png"), QSize(), QIcon::Active, QIcon::On);
        bTrim->setIcon(icon);
        bTrim->setIconSize(QSize(32, 32));
        bTrim->setCheckable(true);
        bTrim->setChecked(false);
        bTrim->setAutoExclusive(false);
        bTrim2 = new QToolButton(QG_CadToolBarMain);
        bTrim2->setObjectName(QString::fromUtf8("bTrim2"));
        bTrim2->setEnabled(true);
        bTrim2->setGeometry(QRect(33, 70, 32, 32));
        bTrim2->setMaximumSize(QSize(32, 32));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/extui/modifytrim2_OFF.png"), QSize(), QIcon::Active, QIcon::Off);
        icon1.addFile(QString::fromUtf8(":/extui/modifytrim2_ON.png"), QSize(), QIcon::Active, QIcon::On);
        bTrim2->setIcon(icon1);
        bTrim2->setIconSize(QSize(32, 32));
        bTrim2->setCheckable(true);
        bTrim2->setChecked(false);
        bTrim2->setAutoExclusive(false);
        bScale = new QToolButton(QG_CadToolBarMain);
        bScale->setObjectName(QString::fromUtf8("bScale"));
        bScale->setEnabled(true);
        bScale->setGeometry(QRect(2, 132, 32, 32));
        bScale->setMaximumSize(QSize(32, 32));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/extui/dlgscale_OFF.png"), QSize(), QIcon::Active, QIcon::Off);
        icon2.addFile(QString::fromUtf8(":/extui/dlgscale_ON.png"), QSize(), QIcon::Active, QIcon::On);
        bScale->setIcon(icon2);
        bScale->setIconSize(QSize(32, 32));
        bScale->setCheckable(true);
        bScale->setChecked(false);
        bScale->setAutoExclusive(false);
        bMove = new QToolButton(QG_CadToolBarMain);
        bMove->setObjectName(QString::fromUtf8("bMove"));
        bMove->setEnabled(true);
        bMove->setGeometry(QRect(2, 101, 32, 32));
        bMove->setMaximumSize(QSize(32, 32));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/extui/modifymove_OFF.png"), QSize(), QIcon::Active, QIcon::Off);
        icon3.addFile(QString::fromUtf8(":/extui/modifymove_ON.png"), QSize(), QIcon::Active, QIcon::On);
        bMove->setIcon(icon3);
        bMove->setIconSize(QSize(32, 32));
        bMove->setCheckable(true);
        bMove->setChecked(false);
        bMove->setAutoExclusive(false);
        bRotate = new QToolButton(QG_CadToolBarMain);
        bRotate->setObjectName(QString::fromUtf8("bRotate"));
        bRotate->setEnabled(true);
        bRotate->setGeometry(QRect(33, 101, 32, 32));
        bRotate->setMaximumSize(QSize(32, 32));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/extui/modifyrotate_OFF.png"), QSize(), QIcon::Active, QIcon::Off);
        icon4.addFile(QString::fromUtf8(":/extui/modifyrotate_ON.png"), QSize(), QIcon::Active, QIcon::On);
        bRotate->setIcon(icon4);
        bRotate->setIconSize(QSize(32, 32));
        bRotate->setCheckable(true);
        bRotate->setChecked(false);
        bRotate->setAutoExclusive(false);
        bMirror = new QToolButton(QG_CadToolBarMain);
        bMirror->setObjectName(QString::fromUtf8("bMirror"));
        bMirror->setEnabled(true);
        bMirror->setGeometry(QRect(33, 132, 32, 32));
        bMirror->setMaximumSize(QSize(32, 32));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/extui/modifymirror_OFF.png"), QSize(), QIcon::Active, QIcon::Off);
        icon5.addFile(QString::fromUtf8(":/extui/modifymirror_ON.png"), QSize(), QIcon::Active, QIcon::On);
        bMirror->setIcon(icon5);
        bMirror->setIconSize(QSize(32, 32));
        bMirror->setCheckable(true);
        bMirror->setChecked(false);
        bMirror->setAutoExclusive(false);
        line = new QFrame(QG_CadToolBarMain);
        line->setObjectName(QString::fromUtf8("line"));
        line->setEnabled(true);
        line->setGeometry(QRect(2, 60, 65, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(QG_CadToolBarMain);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setEnabled(true);
        line_2->setGeometry(QRect(2, 160, 65, 16));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        bCircle = new QToolButton(QG_CadToolBarMain);
        bCircle->setObjectName(QString::fromUtf8("bCircle"));
        bCircle->setEnabled(true);
        bCircle->setGeometry(QRect(33, 33, 32, 32));
        bCircle->setMaximumSize(QSize(32, 32));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/extui/circles_OFF.png"), QSize(), QIcon::Active, QIcon::Off);
        icon6.addFile(QString::fromUtf8(":/extui/circles_ON.png"), QSize(), QIcon::Active, QIcon::On);
        bCircle->setIcon(icon6);
        bCircle->setIconSize(QSize(32, 32));
        bCircle->setCheckable(true);
        bCircle->setChecked(false);
        bCircle->setAutoExclusive(false);
        bNormal = new QToolButton(QG_CadToolBarMain);
        bNormal->setObjectName(QString::fromUtf8("bNormal"));
        bNormal->setEnabled(true);
        bNormal->setGeometry(QRect(2, 2, 32, 32));
        bNormal->setMaximumSize(QSize(32, 32));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/extui/linesnormal_OFF.png"), QSize(), QIcon::Active, QIcon::Off);
        icon7.addFile(QString::fromUtf8(":/extui/linesnormal_ON.png"), QSize(), QIcon::Active, QIcon::On);
        bNormal->setIcon(icon7);
        bNormal->setIconSize(QSize(32, 32));
        bNormal->setCheckable(true);
        bNormal->setChecked(false);
        bNormal->setAutoExclusive(false);
        bRectangle = new QToolButton(QG_CadToolBarMain);
        bRectangle->setObjectName(QString::fromUtf8("bRectangle"));
        bRectangle->setEnabled(true);
        bRectangle->setGeometry(QRect(33, 2, 32, 32));
        bRectangle->setMaximumSize(QSize(32, 32));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/extui/linesrect_OFF.png"), QSize(), QIcon::Active, QIcon::Off);
        icon8.addFile(QString::fromUtf8(":/extui/linesrect_ON.png"), QSize(), QIcon::Active, QIcon::On);
        bRectangle->setIcon(icon8);
        bRectangle->setIconSize(QSize(32, 32));
        bRectangle->setCheckable(true);
        bRectangle->setChecked(false);
        bRectangle->setAutoExclusive(false);
        bArc = new QToolButton(QG_CadToolBarMain);
        bArc->setObjectName(QString::fromUtf8("bArc"));
        bArc->setEnabled(true);
        bArc->setGeometry(QRect(2, 33, 32, 32));
        bArc->setMaximumSize(QSize(32, 32));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/extui/arcscraa_OFF.png"), QSize(), QIcon::Active, QIcon::Off);
        icon9.addFile(QString::fromUtf8(":/extui/arcscraa_ON.png"), QSize(), QIcon::Active, QIcon::On);
        bArc->setIcon(icon9);
        bArc->setIconSize(QSize(32, 32));
        bArc->setCheckable(true);
        bArc->setChecked(false);
        bArc->setAutoExclusive(false);
        line_3 = new QFrame(QG_CadToolBarMain);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setEnabled(true);
        line_3->setGeometry(QRect(4, 230, 60, 16));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        bDel = new QToolButton(QG_CadToolBarMain);
        bDel->setObjectName(QString::fromUtf8("bDel"));
        bDel->setEnabled(true);
        bDel->setGeometry(QRect(33, 202, 32, 32));
        bDel->setMaximumSize(QSize(32, 32));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/extui/delete.png"), QSize(), QIcon::Active, QIcon::Off);
        icon10.addFile(QString::fromUtf8(":/extui/delete.png"), QSize(), QIcon::Active, QIcon::On);
        bDel->setIcon(icon10);
        bDel->setIconSize(QSize(32, 32));
        bDel->setCheckable(true);
        bDel->setAutoRepeat(false);
        bDel->setAutoExclusive(false);
        bDel->setAutoRepeatDelay(500);
        bUnAll = new QToolButton(QG_CadToolBarMain);
        bUnAll->setObjectName(QString::fromUtf8("bUnAll"));
        bUnAll->setEnabled(true);
        bUnAll->setGeometry(QRect(2, 171, 32, 32));
        bUnAll->setMaximumSize(QSize(32, 32));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/extui/selectnothing_OFF.png"), QSize(), QIcon::Active, QIcon::Off);
        icon11.addFile(QString::fromUtf8(":/extui/selectnothing_ON.png"), QSize(), QIcon::Active, QIcon::On);
        bUnAll->setIcon(icon11);
        bUnAll->setIconSize(QSize(32, 32));
        bUnAll->setCheckable(true);
        bUnAll->setAutoRepeat(false);
        bUnAll->setAutoExclusive(false);
        bAll = new QToolButton(QG_CadToolBarMain);
        bAll->setObjectName(QString::fromUtf8("bAll"));
        bAll->setEnabled(true);
        bAll->setGeometry(QRect(33, 171, 32, 32));
        bAll->setMaximumSize(QSize(32, 32));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/extui/selectall_OFF.png"), QSize(), QIcon::Active, QIcon::Off);
        icon12.addFile(QString::fromUtf8(":/extui/selectall_ON.png"), QSize(), QIcon::Active, QIcon::On);
        bAll->setIcon(icon12);
        bAll->setIconSize(QSize(32, 32));
        bAll->setCheckable(true);
        bAll->setAutoRepeat(false);
        bAll->setAutoExclusive(false);
        bInvert = new QToolButton(QG_CadToolBarMain);
        bInvert->setObjectName(QString::fromUtf8("bInvert"));
        bInvert->setEnabled(true);
        bInvert->setGeometry(QRect(2, 202, 32, 32));
        bInvert->setMaximumSize(QSize(32, 32));
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/extui/selectinvert_OFF.png"), QSize(), QIcon::Active, QIcon::Off);
        icon13.addFile(QString::fromUtf8(":/extui/selectinvert_ON.png"), QSize(), QIcon::Active, QIcon::On);
        bInvert->setIcon(icon13);
        bInvert->setIconSize(QSize(32, 32));
        bInvert->setCheckable(true);
        bInvert->setAutoRepeat(false);
        bInvert->setAutoExclusive(false);
        lCoord1 = new QLabel(QG_CadToolBarMain);
        lCoord1->setObjectName(QString::fromUtf8("lCoord1"));
        lCoord1->setGeometry(QRect(3, 242, 60, 20));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font.setPointSize(9);
        lCoord1->setFont(font);
        lCoord1->setFrameShape(QFrame::NoFrame);
        lCoord1->setFrameShadow(QFrame::Plain);
        lCoord1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lCoord1->setWordWrap(false);
        lCoord1b = new QLabel(QG_CadToolBarMain);
        lCoord1b->setObjectName(QString::fromUtf8("lCoord1b"));
        lCoord1b->setGeometry(QRect(3, 262, 60, 20));
        lCoord1b->setFont(font);
        lCoord1b->setFrameShape(QFrame::NoFrame);
        lCoord1b->setFrameShadow(QFrame::Plain);
        lCoord1b->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lCoord1b->setWordWrap(false);
        lGridGap = new QLabel(QG_CadToolBarMain);
        lGridGap->setObjectName(QString::fromUtf8("lGridGap"));
        lGridGap->setGeometry(QRect(3, 283, 60, 20));
        lGridGap->setFont(font);
        lGridGap->setFrameShape(QFrame::NoFrame);
        lGridGap->setFrameShadow(QFrame::Plain);
        lGridGap->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lGridGap->setWordWrap(false);

        retranslateUi(QG_CadToolBarMain);

        QMetaObject::connectSlotsByName(QG_CadToolBarMain);
    } // setupUi

    void retranslateUi(QWidget *QG_CadToolBarMain)
    {
        QG_CadToolBarMain->setWindowTitle(QApplication::translate("QG_CadToolBarMain", "Main", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        bHidden->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        bHidden->setText(QString());
#ifndef QT_NO_TOOLTIP
        bTrim->setToolTip(QApplication::translate("QG_CadToolBarMain", "\344\277\256\345\211\2521", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        bTrim->setText(QString());
#ifndef QT_NO_TOOLTIP
        bTrim2->setToolTip(QApplication::translate("QG_CadToolBarMain", "\344\277\256\345\211\2522", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        bTrim2->setText(QString());
#ifndef QT_NO_TOOLTIP
        bScale->setToolTip(QApplication::translate("QG_CadToolBarMain", "\347\274\251\346\224\276: \350\257\267\345\205\210\351\200\211\346\213\251\345\233\276\345\275\242\345\220\216\357\274\214\345\206\215\346\211\247\350\241\214\347\274\251\346\224\276\345\212\237\350\203\275!", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        bScale->setText(QString());
#ifndef QT_NO_TOOLTIP
        bMove->setToolTip(QApplication::translate("QG_CadToolBarMain", "\345\271\263\347\247\273: \350\257\267\345\205\210\351\200\211\346\213\251\345\233\276\345\275\242\345\220\216\357\274\214\345\206\215\346\211\247\350\241\214\345\271\263\347\247\273\345\212\237\350\203\275!", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        bMove->setText(QString());
#ifndef QT_NO_TOOLTIP
        bRotate->setToolTip(QApplication::translate("QG_CadToolBarMain", "\346\227\213\350\275\254: \350\257\267\345\205\210\351\200\211\346\213\251\345\233\276\345\275\242\345\220\216\357\274\214\345\206\215\346\211\247\350\241\214\346\227\213\350\275\254\345\212\237\350\203\275!", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        bRotate->setText(QString());
#ifndef QT_NO_TOOLTIP
        bMirror->setToolTip(QApplication::translate("QG_CadToolBarMain", "\351\225\234\345\203\217: \350\257\267\345\205\210\351\200\211\346\213\251\345\233\276\345\275\242\345\220\216\357\274\214\345\206\215\346\211\247\350\241\214\351\225\234\345\203\217\345\212\237\350\203\275!", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        bMirror->setText(QString());
#ifndef QT_NO_TOOLTIP
        bCircle->setToolTip(QApplication::translate("QG_CadToolBarMain", "\345\234\206", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        bCircle->setText(QString());
#ifndef QT_NO_TOOLTIP
        bNormal->setToolTip(QApplication::translate("QG_CadToolBarMain", "\347\272\277\346\256\265", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        bNormal->setText(QString());
#ifndef QT_NO_TOOLTIP
        bRectangle->setToolTip(QApplication::translate("QG_CadToolBarMain", "\347\237\251\345\275\242", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        bRectangle->setText(QString());
#ifndef QT_NO_TOOLTIP
        bArc->setToolTip(QApplication::translate("QG_CadToolBarMain", "\345\234\206\345\274\247", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        bArc->setText(QString());
#ifndef QT_NO_TOOLTIP
        bDel->setToolTip(QApplication::translate("QG_CadToolBarMain", "\345\210\240\351\231\244", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        bDel->setText(QString());
#ifndef QT_NO_TOOLTIP
        bUnAll->setToolTip(QApplication::translate("QG_CadToolBarMain", "\346\224\276\345\274\203\351\200\211\346\213\251", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        bUnAll->setText(QString());
#ifndef QT_NO_TOOLTIP
        bAll->setToolTip(QApplication::translate("QG_CadToolBarMain", "\345\205\250\351\200\211", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        bAll->setText(QString());
#ifndef QT_NO_TOOLTIP
        bInvert->setToolTip(QApplication::translate("QG_CadToolBarMain", "\345\217\215\351\200\211", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        bInvert->setText(QString());
        lCoord1->setText(QApplication::translate("QG_CadToolBarMain", "0.0000", 0, QApplication::UnicodeUTF8));
        lCoord1b->setText(QApplication::translate("QG_CadToolBarMain", "0.0000", 0, QApplication::UnicodeUTF8));
        lGridGap->setText(QApplication::translate("QG_CadToolBarMain", "10", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QG_CadToolBarMain: public Ui_QG_CadToolBarMain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QG_CADTOOLBARMAIN_H

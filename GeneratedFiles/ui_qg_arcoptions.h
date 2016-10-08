/********************************************************************************
** Form generated from reading UI file 'qg_arcoptions.ui'
**
** Created: Mon Sep 26 14:56:11 2016
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QG_ARCOPTIONS_H
#define UI_QG_ARCOPTIONS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QG_ArcOptions
{
public:
    QPushButton *pushButton_next;
    QPushButton *pushButton_ok;
    QLabel *label_5;
    QLabel *label;
    QLineEdit *lineEdit_startY;
    QLabel *label_6;
    QLabel *label_4;
    QLineEdit *lineEdit_endX;
    QLabel *label_3;
    QLineEdit *lineEdit_endY;
    QLabel *label_2;
    QLineEdit *lineEdit_startX;
    QLabel *lbInfor;
    QRadioButton *rbNeg;
    QFrame *sep1;
    QRadioButton *rbPos;

    void setupUi(QWidget *QG_ArcOptions)
    {
        if (QG_ArcOptions->objectName().isEmpty())
            QG_ArcOptions->setObjectName(QString::fromUtf8("QG_ArcOptions"));
        QG_ArcOptions->resize(409, 28);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QG_ArcOptions->sizePolicy().hasHeightForWidth());
        QG_ArcOptions->setSizePolicy(sizePolicy);
        QG_ArcOptions->setMinimumSize(QSize(96, 25));
        pushButton_next = new QPushButton(QG_ArcOptions);
        pushButton_next->setObjectName(QString::fromUtf8("pushButton_next"));
        pushButton_next->setGeometry(QRect(364, 52, 51, 23));
        pushButton_ok = new QPushButton(QG_ArcOptions);
        pushButton_ok->setObjectName(QString::fromUtf8("pushButton_ok"));
        pushButton_ok->setGeometry(QRect(455, 52, 41, 23));
        label_5 = new QLabel(QG_ArcOptions);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(41, 53, 24, 16));
        label = new QLabel(QG_ArcOptions);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(131, 54, 16, 16));
        lineEdit_startY = new QLineEdit(QG_ArcOptions);
        lineEdit_startY->setObjectName(QString::fromUtf8("lineEdit_startY"));
        lineEdit_startY->setGeometry(QRect(143, 54, 39, 20));
        label_6 = new QLabel(QG_ArcOptions);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(191, 53, 24, 16));
        label_4 = new QLabel(QG_ArcOptions);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(222, 54, 16, 16));
        lineEdit_endX = new QLineEdit(QG_ArcOptions);
        lineEdit_endX->setObjectName(QString::fromUtf8("lineEdit_endX"));
        lineEdit_endX->setGeometry(QRect(234, 54, 39, 20));
        label_3 = new QLabel(QG_ArcOptions);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(281, 54, 16, 16));
        lineEdit_endY = new QLineEdit(QG_ArcOptions);
        lineEdit_endY->setObjectName(QString::fromUtf8("lineEdit_endY"));
        lineEdit_endY->setGeometry(QRect(293, 54, 39, 20));
        label_2 = new QLabel(QG_ArcOptions);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(72, 54, 16, 16));
        lineEdit_startX = new QLineEdit(QG_ArcOptions);
        lineEdit_startX->setObjectName(QString::fromUtf8("lineEdit_startX"));
        lineEdit_startX->setGeometry(QRect(84, 54, 39, 20));
        lbInfor = new QLabel(QG_ArcOptions);
        lbInfor->setObjectName(QString::fromUtf8("lbInfor"));
        lbInfor->setGeometry(QRect(100, 5, 291, 21));
        QFont font;
        font.setPointSize(11);
        lbInfor->setFont(font);
        rbNeg = new QRadioButton(QG_ArcOptions);
        rbNeg->setObjectName(QString::fromUtf8("rbNeg"));
        rbNeg->setGeometry(QRect(57, 8, 41, 16));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/extui/dirneg.png"), QSize(), QIcon::Normal, QIcon::Off);
        rbNeg->setIcon(icon);
        rbNeg->setCheckable(true);
        sep1 = new QFrame(QG_ArcOptions);
        sep1->setObjectName(QString::fromUtf8("sep1"));
        sep1->setGeometry(QRect(41, 6, 16, 20));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(sep1->sizePolicy().hasHeightForWidth());
        sep1->setSizePolicy(sizePolicy1);
        sep1->setFrameShape(QFrame::VLine);
        sep1->setFrameShadow(QFrame::Sunken);
        rbPos = new QRadioButton(QG_ArcOptions);
        rbPos->setObjectName(QString::fromUtf8("rbPos"));
        rbPos->setGeometry(QRect(8, 8, 41, 16));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/extui/dirpos.png"), QSize(), QIcon::Normal, QIcon::Off);
        rbPos->setIcon(icon1);
        rbPos->setChecked(true);

        retranslateUi(QG_ArcOptions);
        QObject::connect(rbPos, SIGNAL(toggled(bool)), QG_ArcOptions, SLOT(updateDirection(bool)));
        QObject::connect(rbNeg, SIGNAL(toggled(bool)), QG_ArcOptions, SLOT(updateDirection(bool)));

        QMetaObject::connectSlotsByName(QG_ArcOptions);
    } // setupUi

    void retranslateUi(QWidget *QG_ArcOptions)
    {
        QG_ArcOptions->setWindowTitle(QApplication::translate("QG_ArcOptions", "Arc Options", 0, QApplication::UnicodeUTF8));
        pushButton_next->setText(QApplication::translate("QG_ArcOptions", "\344\270\213\344\270\200\344\270\252", 0, QApplication::UnicodeUTF8));
        pushButton_ok->setText(QApplication::translate("QG_ArcOptions", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("QG_ArcOptions", "\350\265\267\347\202\271", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("QG_ArcOptions", "Y:", 0, QApplication::UnicodeUTF8));
        lineEdit_startY->setText(QApplication::translate("QG_ArcOptions", "0", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("QG_ArcOptions", "\347\273\210\347\202\271", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("QG_ArcOptions", "X:", 0, QApplication::UnicodeUTF8));
        lineEdit_endX->setText(QApplication::translate("QG_ArcOptions", "0", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("QG_ArcOptions", "Y:", 0, QApplication::UnicodeUTF8));
        lineEdit_endY->setText(QApplication::translate("QG_ArcOptions", "0", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("QG_ArcOptions", "X:", 0, QApplication::UnicodeUTF8));
        lineEdit_startX->setText(QApplication::translate("QG_ArcOptions", "0", 0, QApplication::UnicodeUTF8));
        lbInfor->setText(QApplication::translate("QG_ArcOptions", "\351\200\211\346\213\251\351\241\272/\351\200\206\345\234\206\345\274\247\345\220\216,\345\215\225\345\207\273\345\267\246\351\224\256\347\241\256\345\256\232\347\273\210\347\202\271\345\235\220\346\240\207.", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        rbNeg->setToolTip(QApplication::translate("QG_ArcOptions", "\351\241\272\346\227\266\351\222\210\346\226\271\345\220\221", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        rbNeg->setText(QString());
#ifndef QT_NO_TOOLTIP
        rbPos->setToolTip(QApplication::translate("QG_ArcOptions", "\351\200\206\346\227\266\351\222\210\346\226\271\345\220\221", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        rbPos->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class QG_ArcOptions: public Ui_QG_ArcOptions {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QG_ARCOPTIONS_H

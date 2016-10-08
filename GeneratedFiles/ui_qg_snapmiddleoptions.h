/********************************************************************************
** Form generated from reading UI file 'qg_snapmiddleoptions.ui'
**
** Created: Mon Sep 26 14:56:11 2016
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QG_SNAPMIDDLEOPTIONS_H
#define UI_QG_SNAPMIDDLEOPTIONS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpinBox>
#include <QtGui/QWidget>
#include "rs_circle.h"
#include "rs_settings.h"

QT_BEGIN_NAMESPACE

class Ui_QG_SnapMiddleOptions
{
public:
    QLabel *lDist;
    QSpinBox *sbMiddlePoints;

    void setupUi(QWidget *QG_SnapMiddleOptions)
    {
        if (QG_SnapMiddleOptions->objectName().isEmpty())
            QG_SnapMiddleOptions->setObjectName(QString::fromUtf8("QG_SnapMiddleOptions"));
        QG_SnapMiddleOptions->resize(135, 24);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QG_SnapMiddleOptions->sizePolicy().hasHeightForWidth());
        QG_SnapMiddleOptions->setSizePolicy(sizePolicy);
        QG_SnapMiddleOptions->setMinimumSize(QSize(135, 22));
        QG_SnapMiddleOptions->setMaximumSize(QSize(155, 24));
        QG_SnapMiddleOptions->setMouseTracking(true);
        lDist = new QLabel(QG_SnapMiddleOptions);
        lDist->setObjectName(QString::fromUtf8("lDist"));
        lDist->setGeometry(QRect(1, 1, 91, 22));
        lDist->setWordWrap(false);
        sbMiddlePoints = new QSpinBox(QG_SnapMiddleOptions);
        sbMiddlePoints->setObjectName(QString::fromUtf8("sbMiddlePoints"));
        sbMiddlePoints->setGeometry(QRect(93, 1, 40, 22));
        sbMiddlePoints->setMinimum(1);
        sbMiddlePoints->setValue(1);

        retranslateUi(QG_SnapMiddleOptions);

        QMetaObject::connectSlotsByName(QG_SnapMiddleOptions);
    } // setupUi

    void retranslateUi(QWidget *QG_SnapMiddleOptions)
    {
        QG_SnapMiddleOptions->setWindowTitle(QApplication::translate("QG_SnapMiddleOptions", "Snap Distance Options", 0, QApplication::UnicodeUTF8));
        lDist->setText(QApplication::translate("QG_SnapMiddleOptions", "\344\270\255\351\227\264\347\202\271\346\225\260", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        sbMiddlePoints->setToolTip(QApplication::translate("QG_SnapMiddleOptions", "Number of equidistant division points", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    } // retranslateUi

};

namespace Ui {
    class QG_SnapMiddleOptions: public Ui_QG_SnapMiddleOptions {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QG_SNAPMIDDLEOPTIONS_H

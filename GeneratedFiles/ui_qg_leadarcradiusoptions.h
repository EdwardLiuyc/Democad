/********************************************************************************
** Form generated from reading UI file 'qg_leadarcradiusoptions.ui'
**
** Created: Mon Sep 26 14:56:11 2016
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QG_LEADARCRADIUSOPTIONS_H
#define UI_QG_LEADARCRADIUSOPTIONS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QG_LeadArcRadiusOptions
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit_radius;

    void setupUi(QWidget *QG_LeadArcRadiusOptions)
    {
        if (QG_LeadArcRadiusOptions->objectName().isEmpty())
            QG_LeadArcRadiusOptions->setObjectName(QString::fromUtf8("QG_LeadArcRadiusOptions"));
        QG_LeadArcRadiusOptions->resize(100, 22);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QG_LeadArcRadiusOptions->sizePolicy().hasHeightForWidth());
        QG_LeadArcRadiusOptions->setSizePolicy(sizePolicy);
        QG_LeadArcRadiusOptions->setMaximumSize(QSize(200, 16777215));
        gridLayout = new QGridLayout(QG_LeadArcRadiusOptions);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(QG_LeadArcRadiusOptions);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lineEdit_radius = new QLineEdit(QG_LeadArcRadiusOptions);
        lineEdit_radius->setObjectName(QString::fromUtf8("lineEdit_radius"));

        horizontalLayout->addWidget(lineEdit_radius);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        retranslateUi(QG_LeadArcRadiusOptions);

        QMetaObject::connectSlotsByName(QG_LeadArcRadiusOptions);
    } // setupUi

    void retranslateUi(QWidget *QG_LeadArcRadiusOptions)
    {
        QG_LeadArcRadiusOptions->setWindowTitle(QApplication::translate("QG_LeadArcRadiusOptions", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("QG_LeadArcRadiusOptions", "\345\215\212\345\276\204", 0, QApplication::UnicodeUTF8));
        lineEdit_radius->setText(QApplication::translate("QG_LeadArcRadiusOptions", " 5", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QG_LeadArcRadiusOptions: public Ui_QG_LeadArcRadiusOptions {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QG_LEADARCRADIUSOPTIONS_H

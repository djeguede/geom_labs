/********************************************************************************
** Form generated from reading UI file 'grahamwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRAHAMWIDGET_H
#define UI_GRAHAMWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GrahamWidget
{
public:

    void setupUi(QWidget *GrahamWidget)
    {
        if (GrahamWidget->objectName().isEmpty())
            GrahamWidget->setObjectName(QStringLiteral("GrahamWidget"));
        GrahamWidget->resize(718, 443);

        retranslateUi(GrahamWidget);

        QMetaObject::connectSlotsByName(GrahamWidget);
    } // setupUi

    void retranslateUi(QWidget *GrahamWidget)
    {
        GrahamWidget->setWindowTitle(QApplication::translate("GrahamWidget", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class GrahamWidget: public Ui_GrahamWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAHAMWIDGET_H

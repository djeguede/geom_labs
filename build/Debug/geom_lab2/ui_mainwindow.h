/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "grahamwidget.h"
#include "qcustomplot.h"
#include "widget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QCustomPlot *customPlot;
    QLabel *label;
    GrahamWidget *graham;
    Widget *jarvis;
    QVBoxLayout *verticalLayout;
    QSpinBox *spinBox;
    QPushButton *graham_button;
    QPushButton *jarvis_button;
    QPushButton *plot_button;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        customPlot = new QCustomPlot(centralwidget);
        customPlot->setObjectName(QStringLiteral("customPlot"));

        gridLayout->addWidget(customPlot, 0, 1, 2, 2);

        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 1, 1, 1, 1);

        graham = new GrahamWidget(centralwidget);
        graham->setObjectName(QStringLiteral("graham"));

        gridLayout->addWidget(graham, 0, 0, 1, 1);

        jarvis = new Widget(centralwidget);
        jarvis->setObjectName(QStringLiteral("jarvis"));

        gridLayout->addWidget(jarvis, 1, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        spinBox = new QSpinBox(centralwidget);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setMaximum(100000);
        spinBox->setValue(30);

        verticalLayout->addWidget(spinBox);

        graham_button = new QPushButton(centralwidget);
        graham_button->setObjectName(QStringLiteral("graham_button"));

        verticalLayout->addWidget(graham_button);

        jarvis_button = new QPushButton(centralwidget);
        jarvis_button->setObjectName(QStringLiteral("jarvis_button"));

        verticalLayout->addWidget(jarvis_button);

        plot_button = new QPushButton(centralwidget);
        plot_button->setObjectName(QStringLiteral("plot_button"));

        verticalLayout->addWidget(plot_button);


        gridLayout->addLayout(verticalLayout, 2, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        label->setText(QString());
        graham_button->setText(QApplication::translate("MainWindow", "Graham Demo", 0));
        jarvis_button->setText(QApplication::translate("MainWindow", "Jarvis Demo", 0));
        plot_button->setText(QApplication::translate("MainWindow", "Plot Graphic", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

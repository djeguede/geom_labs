#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cpoint.h"
#include <QtPrintSupport/QPrinter>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    std::vector<CPoint> jarvis(std::vector<CPoint> lpoints);
    std::vector<CPoint> Merge(std::vector<CPoint>P1,  std::vector<CPoint>P2);
    std::vector<CPoint> divideConq(std::vector<CPoint> vertex );

private:
    Ui::MainWindow *ui;

public:
    static CPoint pivotP1;
    static CPoint pivotP2;
};

#endif // MAINWINDOW_H

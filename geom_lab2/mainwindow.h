#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cpoint.h"
#include <QtPrintSupport/QPrinter>
#include "widget.h"
#include "grahamwidget.h"

namespace Ui {
class MainWindow;
}



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
     friend bool POLAR_ORDER(CPoint a, CPoint b);
     std::vector<CPoint> grahamScan(std::vector<CPoint> lpoints);
     std::vector<CPoint> jarvis(std::vector<CPoint> lpoints);

public slots:
    void drawGraphic();
    void demoGraham();
    void demoJarvis();

private:
    Ui::MainWindow *ui;
    std::vector<CPoint> points;
    std::vector<CPoint> graham_result;
    std::vector<CPoint> javic_result;
    static CPoint pivot;
    ofstream login;
    QVector<double> n;
    QVector<double> nlogn;
    QVector<double> gr;
    QVector<double> jarv;
    QFile file2;
    QPainter paint_gr;
    QPainter paint_jarv;
    Widget w;
    GrahamWidget w_gr;

};

#endif // MAINWINDOW_H

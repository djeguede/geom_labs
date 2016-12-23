#include "mainwindow.h"
#include "ui_mainwindow.h"


#include "sweepline.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    /*
    vector<seg>  vecseq ;
    int w= this->width();
    int h= this->height();

    QPainter  paint_swl(this);
    paint_swl.setPen(QPen(Qt::black,1, Qt::SolidLine));
    paint_swl.setBrush(QBrush(Qt::black, Qt::SolidPattern));

    srand(time(NULL));
    for(int i=1; i<=15 ;i++)
    {
        double x1= rand()%(w-50);
        double y1= rand()%(h-50);

        double x2= rand()%(w-50);
        double y2= rand()%(h-50);

        paint_swl.drawLine(QPoint(x1,y1), QPoint(x2,y2));
        vecseq.push_back( seg(pt(x1,y1), pt(x2, y2), i) );
    }

    set< pair<int, int> > p= solve(vecseq);
    qDebug()<<"p.size(): "<<p.size() ;

    paint_swl.setPen(QPen(Qt::blue,2, Qt::SolidLine));
    paint_swl.setBrush(QBrush(Qt::blue, Qt::SolidPattern));
    for( int j=0; j<vecseq.size(); j++)
    {
        //if(vecseq[j].id==p.first)
        {
            paint_swl.drawLine( QPoint(vecseq[j].p.x,vecseq[j].p.y), QPoint(vecseq[j].q.x,vecseq[j].q.y) );

        }

        //if(vecseq[j].id==p.second)
        {
             //paint_swl.drawLine(QPoint(x1,y1), QPoint(x2,y2));
             paint_swl.drawLine( QPoint(vecseq[j].p.x,vecseq[j].p.y), QPoint(vecseq[j].q.x,vecseq[j].q.y) );
        }
    }

    paint_swl.end();
    */
}

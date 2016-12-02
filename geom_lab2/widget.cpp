#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *e)
{
    std::vector<CPoint> lpoints;
    std::vector<CPoint> vpts;
    int w= this->width();
    int h= this->height();
    QPainter paint_jarv(this);
    qDebug()<<"demoJarvis w: "<<w<<" h: "<<h;

    paint_jarv.setPen(QPen(Qt::black,3, Qt::SolidLine));
    paint_jarv.setBrush(QBrush(Qt::black, Qt::SolidPattern));


    for(int i=1; i<=30 ;i++)
    {
        int x= rand()%(w-5);
        int y= rand()%(h-5);
        lpoints.push_back(CPoint(x,y));
        paint_jarv.drawPoint(QPoint(x,y));
        //qDebug()<<"demoJarvis x: "<<x<<" y: "<<y;
    }
//****************************************************************


    std::vector<CPoint> result;
    QVector<QPoint> test;
    int i=0;
    CPoint min;

    for(unsigned int j=0; j<lpoints.size(); j++)
    {
      if(lpoints[j].getX()<lpoints[i].getX() || (lpoints[j].getX()==lpoints[i].getX() &&lpoints[j].getY()<lpoints[i].getY() ))
      {
          i=j;
      }
    }

    min=lpoints[i];
    paint_jarv.setPen(QPen(Qt::red,5, Qt::SolidLine));//
    paint_jarv.setBrush(QBrush(Qt::red, Qt::SolidPattern));//
    paint_jarv.drawPoint(QPoint(min.getX(),min.getY()));//
    int p=i , q;


    do{
        result.push_back(lpoints[p]);
        test.push_back(QPoint(lpoints[p].getX(), lpoints[p].getY()));//

        //Sleep(1000*3);

        q=(p+1)%lpoints.size();

        for(unsigned int j=0; j < lpoints.size(); j++)
        {
            if( ccw( lpoints[p], lpoints[j] ,lpoints[q] ) == -1 )  q=j;
        }

      p= q;

      paint_jarv.setPen(QPen(Qt::blue,1, Qt::SolidLine));//
      paint_jarv.setBrush(QBrush(Qt::blue, Qt::SolidPattern));//
      paint_jarv.drawLine(test.back(), QPoint(lpoints[p].getX(), lpoints[p].getY()) );//
    }while(p!=i);



    paint_jarv.end();
}

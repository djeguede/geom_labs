#include "grahamwidget.h"
#include "ui_grahamwidget.h"

CPoint GrahamWidget::pivot= CPoint();

GrahamWidget::GrahamWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GrahamWidget)
{
    ui->setupUi(this);
}

GrahamWidget::~GrahamWidget()
{
    delete ui;
}

void GrahamWidget::paintEvent(QPaintEvent *e)
{
    std::vector<CPoint> lpoints;
    std::vector<CPoint> result;
    QVector<QPoint> test;
    int w= this->width();
    int h= this->height();


    QPainter  paint_gr(this);
    qDebug()<<"demoGraham w: "<<w<<" h: "<<h;
    paint_gr.setPen(QPen(Qt::black,3, Qt::SolidLine));
    paint_gr.setBrush(QBrush(Qt::black, Qt::SolidPattern));


    for(int i=1; i<=30 ;i++)
    {
        int x= rand()%(w-5);
        int y= rand()%(h-50);
        lpoints.push_back(CPoint(x,y));
        paint_gr.drawPoint(QPoint(x,h-y));
        //qDebug()<<"demoGraham x: "<<x<<" y: "<<y;
    }

//************************************************************************************
    auto min =std::min_element(lpoints.begin(),lpoints.end());
    paint_gr.setPen(QPen(Qt::blue, 6, Qt::SolidLine));
    paint_gr.setBrush(QBrush(Qt::blue, Qt::SolidPattern));
    paint_gr.drawPoint(QPoint((*min).getX(),h-(*min).getY()));

    GrahamWidget::pivot =*min;
    swapp(*lpoints.begin(), *min);

    sort( lpoints.begin()+1, lpoints.end(), [&](CPoint a, CPoint b)-> bool
    {
        int order = ccw(GrahamWidget::pivot, a, b);
        if (order == 0)
            return distSq(GrahamWidget::pivot, a) < distSq(GrahamWidget::pivot, b);
        return (order == -1);

    } );

    std::vector<CPoint>::iterator it;
    it=lpoints.begin();
    for(it; it<lpoints.begin()+2; it++ )
    {
      result.push_back(*it);
      paint_gr.setPen(QPen(Qt::red, 1, Qt::SolidLine));
      paint_gr.setBrush(QBrush(Qt::red, Qt::SolidPattern));
      paint_gr.drawLine(QPoint( (*it).getX(), h-(*it).getY() ), QPoint( (*(it+1)).getX() ,  h-(*(it+1)).getY()  ));
       //QThread::msleep(100);
    }

    for(int j=0; j<lpoints.size(); j++)
    {
        paint_gr.setPen(QPen(Qt::black, 1, Qt::SolidLine));
        paint_gr.setBrush(QBrush(Qt::black, Qt::SolidPattern));
        paint_gr.drawLine(QPoint(lpoints[j].getX(), h-lpoints[j].getY()), QPoint( lpoints[(j+1)%lpoints.size()].getX(), h-lpoints[(j+1)%lpoints.size()].getY()) );
    }


    for(int i=3; i<lpoints.size(); i++)
    {
        CPoint pback= result.back();
        result.pop_back();

        while( ccw(result.back(), pback, lpoints[i]) != -1 && result.size() > 1 )
        {
             pback= result.back();
             result.pop_back();

        }

        result.push_back(pback);
        result.push_back(lpoints[i]);

        paint_gr.setPen(QPen(Qt::green, 1, Qt::SolidLine));
        paint_gr.setBrush(QBrush(Qt::green, Qt::SolidPattern));
        paint_gr.drawLine(QPoint(pback.getX(), h-pback.getY()), QPoint(lpoints[i].getX() ,h-lpoints[i].getY() ));
        //QThread::msleep(100);
    }


    paint_gr.setPen(QPen(Qt::yellow, 1, Qt::DotLine));
    paint_gr.setBrush(QBrush(Qt::yellow, Qt::SolidPattern));
    paint_gr.drawLine(QPoint( result.back().getX() , h-result.back().getY()) , QPoint( (*(result.begin())).getX()  ,h- (*(result.begin())).getY()));


    //****** Проверка
    for(int j=0; j<result.size(); j++)
    {
        paint_gr.setPen(QPen(Qt::red, 1, Qt::SolidLine));
        paint_gr.setBrush(QBrush(Qt::red, Qt::SolidPattern));
        paint_gr.drawLine(QPoint(result[j].getX(), h-result[j].getY()), QPoint( result[(j+1)%result.size()].getX(), h-result[(j+1)%result.size()].getY()) );
    }
    //*** конец проверки*/
    paint_gr.end();

}

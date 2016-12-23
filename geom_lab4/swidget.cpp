#include "swidget.h"
#include "ui_swidget.h"


//#include "segment_intersection.h"

SWidget::SWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SWidget)
{
    ui->setupUi(this);
}

SWidget::~SWidget()
{
    delete ui;
}

void SWidget::paintEvent(QPaintEvent *e)
{
    vector<seg>  vecseq ;
    int w= this->width();
    int h= this->height();

    QPainter  paint_swl(this);
    paint_swl.setPen(QPen(Qt::black,2, Qt::SolidLine));
    paint_swl.setBrush(QBrush(Qt::black, Qt::SolidPattern));

    srand(time(NULL));
    for(int i=1; i<=15 ;i++)
    {
        int x1= rand()%(w-5);
        int y1= rand()%(h-5);

        int x2= rand()%(w-5);
        int y2= rand()%(h-5);

        paint_swl.drawLine(QPoint(x1,y1), QPoint(x2,y2));
        vecseq.push_back( seg(pt(x1,y1), pt(x2, y2) ) );
    }


    set< pair<int, int> > resultat= solve(vecseq);
    qDebug()<<"resultat.size(): "<<resultat.size() ;

    paint_swl.setPen(QPen(Qt::blue,2, Qt::SolidLine));
    paint_swl.setBrush(QBrush(Qt::blue, Qt::SolidPattern));

    for(auto k=resultat.begin(); k!=resultat.end(); ++k)
    {
        qDebug()<<(*k).first<<" "<<(*k).second ;
        for(auto t=0; t<vecseq.size(); t++)
        {
           if(t==k->first) paint_swl.drawLine(QPoint(vecseq[t].p.x ,vecseq[t].p.y ), QPoint( vecseq[t].q.x ,vecseq[t].q.y  ));
           if(t==k->second)  paint_swl.drawLine(QPoint(vecseq[t].p.x ,vecseq[t].p.y ), QPoint( vecseq[t].q.x ,vecseq[t].q.y  ));
        }
    }

    paint_swl.end();

}

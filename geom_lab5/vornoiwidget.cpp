#include "vornoiwidget.h"
#include "ui_vornoiwidget.h"

VornoiWidget::VornoiWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VornoiWidget)
{
    ui->setupUi(this);
}

VornoiWidget::~VornoiWidget()
{
    delete ui;
}

void VornoiWidget::paintEvent(QPaintEvent *e)
{
    set<point> sP;
    FortuneAlgorithm FAlgo;
    vector<Voronoi::seg*> Resultat;
    int w= this->width();
    int h= this->height();

    QPainter  paint_vor(this);
    paint_vor.setPen(QPen(Qt::black,3, Qt::SolidLine));
    paint_vor.setBrush(QBrush(Qt::black, Qt::SolidPattern));



    srand(time(NULL));
    for(int i=1; i<=45 ;i++)
    {
        int x1= 50+  rand()%(w-100);
        int y1= 50+ rand()%(h-100);


        paint_vor.drawPoint(QPoint(x1,y1));
        sP.insert( point(x1, y1) );

    }

    Resultat= FAlgo.getVoronoiDiagram(sP);

    paint_vor.setPen(QPen(Qt::red,3, Qt::SolidLine));
    paint_vor.setBrush(QBrush(Qt::red, Qt::SolidPattern));

    for(int j=0; j<Resultat.size(); j++)
    {
        paint_vor.drawLine(QPoint(Resultat[j]->start.first ,Resultat[j]->start.second),  QPoint(Resultat[j]->end.first ,Resultat[j]->end.second) );
    }

    paint_vor.end();
}

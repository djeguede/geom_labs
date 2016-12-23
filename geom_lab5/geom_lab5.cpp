#include "geom_lab5.h"
#include "ui_geom_lab5.h"

geom_lab5::geom_lab5(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::geom_lab5)
{
    ui->setupUi(this);

    QObject::connect(ui->pushButton, SIGNAL(clicked()),this , SLOT( drawGraphic() ));
}

geom_lab5::~geom_lab5()
{
    delete ui;
}

void geom_lab5::drawGraphic()
{

    for(int k=100; k<=ui->spinBox->value(); k+=100)
    {

        set<point> sP;
        FortuneAlgorithm FAlgo;
        vector<Voronoi::seg*> Resultat;


        srand(time(NULL));
        for(int i=1; i<=k ;i++)
        {
            int x1= 50+  rand()%1000;
            int y1= 50+ rand()%1000;


            sP.insert( point(x1, y1) );

        }



        std::clock_t start_lab5 = clock();
            Resultat= FAlgo.getVoronoiDiagram(sP);
        std::clock_t end_lab5 =clock();

        double duration_lab5 = 2000*80* (end_lab5 - start_lab5) / (double) CLOCKS_PER_SEC;

        n.push_back(k);
        nlogn.push_back( k* log(k));
        lab5.push_back( duration_lab5 );

        qDebug()<<"k: "<<k;
    }


    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setPen(QPen(Qt::red));
    //ui->customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));

    ui->customPlot->addGraph();
    ui->customPlot->graph(1)->setPen(QPen(Qt::blue));
    //ui->customPlot->graph(1)->setBrush(QBrush(QColor(0, 255, 0, 20)));

    ui->customPlot->graph(0)->setData(n, nlogn);
    ui->customPlot->graph(1)->setData(n, lab5);

    ui->customPlot->xAxis->setLabel("Количество данных (n)");
    ui->customPlot->yAxis->setLabel("time (t) ");
    ui->customPlot->xAxis->setRange(0, ui->spinBox->value() + 50);
    ui->customPlot->yAxis->setRange(0, ui->spinBox->value() * 10);
    ui->customPlot->replot();
}

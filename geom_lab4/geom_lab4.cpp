#include "geom_lab4.h"
#include "ui_geom_lab4.h"

geom_lab4::geom_lab4(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::geom_lab4)
{
    ui->setupUi(this);

    QObject::connect(ui->pushButton, SIGNAL(clicked()),this , SLOT( drawGraphic() ));
}

geom_lab4::~geom_lab4()
{
    delete ui;
}

void geom_lab4::drawGraphic()
{


    for(int k=50; k<=ui->spinBox->value(); k+=50)
    {
        vector<seg>  vecseq ;

        srand(time(NULL));
        for(int i=1; i<=k ;i++)
        {
            int x1= rand()%(1000000);
            int y1= rand()%(1000000);

            int x2= rand()%(1000000);
            int y2= rand()%(1000000);


            vecseq.push_back( seg(pt(x1,y1), pt(x2, y2) ) );
        }

        std::clock_t start_lab4 = clock();
            set< pair<int, int> > resultat= solve(vecseq);
        std::clock_t end_lab4 =clock();

        double duration_lab4 = 3000* (end_lab4 - start_lab4) / (double) CLOCKS_PER_SEC;

        n.push_back(k);
        nlogn.push_back( k* log(k));
        lab4.push_back( duration_lab4 );

        qDebug()<<"k: "<<k;
    }

    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setPen(QPen(Qt::red));
    //ui->customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));

    ui->customPlot->addGraph();
    ui->customPlot->graph(1)->setPen(QPen(Qt::blue));
    //ui->customPlot->graph(1)->setBrush(QBrush(QColor(0, 255, 0, 20)));

    ui->customPlot->graph(0)->setData(n, nlogn);
    ui->customPlot->graph(1)->setData(n, lab4);

    ui->customPlot->xAxis->setLabel("Количество данных (n)");
    ui->customPlot->yAxis->setLabel("time (t) ");
    ui->customPlot->xAxis->setRange(0, ui->spinBox->value() + 50);
    ui->customPlot->yAxis->setRange(0, ui->spinBox->value() * 10);
    ui->customPlot->replot();
}

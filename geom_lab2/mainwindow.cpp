#include "mainwindow.h"
#include "ui_mainwindow.h"

CPoint MainWindow::pivot= CPoint();

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->plot_button, SIGNAL( clicked() ),this , SLOT( drawGraphic() ));
    QObject::connect(ui->graham_button, SIGNAL(clicked()),this , SLOT( demoGraham() ));
    QObject::connect(ui->jarvis_button, SIGNAL(clicked()),this , SLOT( demoJarvis() ));

}

MainWindow::~MainWindow()
{
    delete ui;
}

bool POLAR_ORDER(CPoint a, CPoint b)
{
    int order = ccw(MainWindow::pivot, a, b);
    if (order == 0)
        return distSq(MainWindow::pivot, a) < distSq(MainWindow::pivot, b);
    return (order == -1);
}


std::vector<CPoint> MainWindow::grahamScan(std::vector<CPoint> lpoints)
{
   std::vector<CPoint> result;
   auto min =std::min_element(lpoints.begin(),lpoints.end());
   MainWindow::pivot=*min;
   swapp(*lpoints.begin(), *min);
   sort( lpoints.begin()+1, lpoints.end(), [&](CPoint a, CPoint b)-> bool
   {
       int order = ccw(MainWindow::pivot, a, b);
       if (order == 0)
           return distSq(MainWindow::pivot, a) < distSq(MainWindow::pivot, b);
       return (order == -1);

   } );

   std::vector<CPoint>::iterator it;
   it=lpoints.begin();
   for(it; it<=lpoints.begin()+2; it++ )
   {
     result.push_back(*it);
   }

   for(unsigned int i=3; i<lpoints.size(); i++)
   {
       CPoint pback= result.back();
       result.pop_back();

       while( ccw(result.back(), pback, lpoints[i]) !=  -1 && result.size() > 1)
       {
            pback= result.back();
            result.pop_back();
       }

       result.push_back(pback);
       result.push_back(lpoints[i]);
   }

   return result;
}

std::vector<CPoint> MainWindow::jarvis(std::vector<CPoint> lpoints)
{
    std::vector<CPoint> result;
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
    int p=i , q;


    do{
        result.push_back(lpoints[p]);
        q=(p+1)%lpoints.size();

        for(unsigned int j=0; j<lpoints.size(); j++)
        {
            if( ccw( lpoints[p], lpoints[j] ,lpoints[q] ) == -1 )  q=j;
        }

      p= q;
    }while(p!=i);


    return result;
}

void MainWindow::drawGraphic()
{
    //Sleep(1000*3);

    file2.setFileName("lab22.txt");
       if (file2.open(QIODevice::WriteOnly | QIODevice::Append)) {
           file2.write("blablabla");
       }

    login.open("lab2.txt");
    login<<"n   \t  (nlog(n)) \t   Graham  \t    Jarvis   \n";
    qDebug()<<"n   \t  (nlog(n)) \t  Graham  \tJarvis   \n";
    for(int k=5; k<=ui->spinBox->value(); k+=5)
    {
        std::vector<CPoint> vpoints;
        srand(time(NULL));

        for(int i=1; i<=k ;i++)
        {
            int x= rand()%500;
            int y= rand()%500;
            vpoints.push_back(CPoint(x,y));
            //qDebug()<<"x: "<<x <<" y: "<<y;
        }

        std::clock_t start_gr = clock();
        std::vector<CPoint> res_gr= grahamScan(vpoints);
        std::clock_t end_gr =clock();

        std::clock_t start_jarv = clock();
        std::vector<CPoint> res_jarv= jarvis(vpoints);
        std::clock_t end_jarv =clock();

        double gr_duration=20*100* (end_gr - start_gr); // / (double) CLOCKS_PER_SEC;
        double jarv_duration= 20*20* (end_jarv - start_jarv );// /(double) CLOCKS_PER_SEC;

        n.push_back(k);
        nlogn.push_back( k* log(k));
        gr.push_back( gr_duration );
        jarv.push_back(jarv_duration );
        login<<k<<"   \t  "<<k* log(k)<< "  \t  "<<gr_duration<< " \t  "<<jarv_duration;
        qDebug()<<k<<"   \t  "<<k* log(k)<< "  \t  "<<gr_duration<< " \t  "<<jarv_duration;

    }


    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setPen(QPen(Qt::red));
    //ui->customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));

    ui->customPlot->addGraph();
    ui->customPlot->graph(1)->setPen(QPen(Qt::blue));
    //ui->customPlot->graph(1)->setBrush(QBrush(QColor(0, 255, 0, 20)));

    ui->customPlot->addGraph();
    ui->customPlot->graph(2)->setPen(QPen(Qt::green));
    //ui->customPlot->graph(2)->setBrush(QBrush(QColor(255, 0, 0, 20)));

    ui->customPlot->addGraph();
    ui->customPlot->graph(3)->setPen(QPen(Qt::black));
    //ui->customPlot->graph(3)->setBrush(QBrush(QColor(0, 0, 0, 20)));

    ui->customPlot->graph(0)->setData(n, gr);
    ui->customPlot->graph(1)->setData(n, jarv);
    ui->customPlot->graph(2)->setData(n, nlogn);
    ui->customPlot->graph(3)->setData(n, n);
    ui->customPlot->xAxis->setLabel("Количество данных (n)");
    ui->customPlot->yAxis->setLabel("time (t) ");
    ui->customPlot->xAxis->setRange(0, ui->spinBox->value() + 50);
    ui->customPlot->yAxis->setRange(0, ui->spinBox->value() * 10);

    ui->customPlot->replot();
    login.close();
    file2.close();
}

void MainWindow::demoGraham()
{
    w_gr.show();
}

void MainWindow::demoJarvis()
{
    w.show();
}

#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    file1.setFileName("res.txt");
       if (file1.open(QIODevice::WriteOnly | QIODevice::Append)) {
           file1.write("blablabla");
       }
       myfile.open("res2.txt");
       myfile<<"n \t  theory(nlog(n)) \t Practice \n";
        for(int k=5; k<=1000 ;k+=5)
        {
            CList<int> list=CList<int>();
            srand(time(NULL));
            for(int i=1; i<=k; i+=1){
                int var= rand()%1000-499;
                list.push_back(var);
            }

            std::clock_t startTime = clock();
            list.sort();
            std::clock_t endTime =clock();
            double duration=20* (endTime- startTime);// /(double) CLOCKS_PER_SEC;
            qDebug()<<"Duration: "<<duration;
            map[k]=duration;
            y_exper.push_back(duration);
            n.push_back(k);
            double dk=k;
            y_theory.push_back( dk * log(dk)/log(10));


            ui->myplot->addGraph();
            ui->myplot->graph(0)->setPen(QPen(Qt::blue));
            ui->myplot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
            ui->myplot->addGraph();
            ui->myplot->graph(1)->setPen(QPen(Qt::red));

            ui->myplot->graph(0)->setData(n, y_exper);
            ui->myplot->graph(1)->setData(n, y_theory);
            ui->myplot->xAxis->setLabel("Количество данных (n)");
            ui->myplot->yAxis->setLabel("time (t) ");
            ui->myplot->xAxis->setRange(0, 1000);
            ui->myplot->yAxis->setRange(0, 4500);

            myfile<<k<<"\t"<< dk * log(dk) / log(10) <<"\t\t\t"<<duration<<"\n";
        }

      ui->myplot->replot();
      myfile.close();
      file1.close();
}

Widget::~Widget()
{
    delete ui;
}

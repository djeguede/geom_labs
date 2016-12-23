#include "mainwindow.h"
#include "ui_mainwindow.h"


CPoint MainWindow::pivotP1= CPoint();
CPoint MainWindow::pivotP2= CPoint();

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



std::vector<CPoint> MainWindow::jarvis(std::vector<CPoint> lpoints)
{
    std::vector<CPoint> result;
    int i=0;
    CPoint min;

    qDebug()<< "jarvis(lpoints)--- lpoints.size()= "<<lpoints.size();

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

std::vector<CPoint> MainWindow::Merge(std::vector<CPoint>P1,  std::vector<CPoint>P2)
{
    std::vector<CPoint> result;
    int rOfLH=0;
    int lOfRH=0;
    int rOfLH2=0;
    int lOfRH2=0;

  if(P1.size()>=3 && P2.size()>=3)
  {
    //********* Упорядочить по ccw**** я сам
    auto minP1 =std::min_element(P1.begin(),P1.end());
    auto minP2 =std::min_element(P2.begin(),P2.end());


    MainWindow::pivotP1 =*minP1;
    swapp(*P1.begin(), *minP1);

    MainWindow::pivotP2 =*minP2;
    swapp(*P2.begin(), *minP2);

    sort( P1.begin()+1, P1.end(), [&](CPoint a, CPoint b)-> bool
    {
        int order = ccw(MainWindow::pivotP1, a, b);
        if (order == 0)
            return distSq(MainWindow::pivotP1, a) < distSq(MainWindow::pivotP1, b);
        return (order == -1);

    } );


    sort( P2.begin()+1, P2.end(), [&](CPoint a, CPoint b)-> bool
    {
        int order = ccw(MainWindow::pivotP2, a, b);
        if (order == 0)
            return distSq(MainWindow::pivotP2, a) < distSq(MainWindow::pivotP2, b);
        return (order == -1);

    } );

    //**************************Начало Merge
    rOfLH=0;
    lOfRH=0;
    rOfLH2=0;
    lOfRH2=0;
    int rLH, lRH, rLH2, lRH2;
    for(int i=1; i<P1.size(); i++)
    {
      if(P1[i].getX()>P1[rOfLH].getX())
      {
          rOfLH=i;
          rOfLH2=i;
      }
    }

    for(int j=1; j<P2.size(); j++)
    {
        if(P2[j].getX()<P2[lOfRH].getX())
        {
            lOfRH=j;
            lOfRH2=j;
        }
    }

    if(rOfLH==0) rLH =P1.size()-1;
    else rLH=rOfLH-1  ;

    if(lOfRH== (P2.size()-1) ) lRH=0;
    else lRH=lOfRH+1;


    //lower tangent
    while( !ccw2(P1[rLH], P1[rOfLH], P2[lOfRH]) || !ccw2(P1[rOfLH], P2[lOfRH], P2[lRH]) )
    {
        //qDebug()<< "P1.size()+ P2.size() = "<<P1.size()+ P2.size();

        while( !ccw2(P1[rLH], P1[rOfLH], P2[lOfRH]) )
        {
            rOfLH--;
            if(rOfLH==-1) rOfLH=P1.size()-1;
            if(rOfLH==0) rLH =P1.size()-1;
            else rLH=rOfLH-1  ;
        }

        while( !ccw2(P1[rOfLH], P2[lOfRH], P2[lRH]) )
        {
            lOfRH++;
            if(lOfRH==P2.size()) lOfRH=0;

            if(lOfRH== (P2.size()-1) ) lRH=0;
            else lRH=lOfRH+1;
        }
    }


    if(lOfRH2==0) lRH2=P2.size()-1; //***
    else lRH2= lOfRH2-1;

    if(rOfLH2 == (P1.size()-1)) rLH2=0; //***
    else rLH2=rOfLH2+1 ;

    //upper tangent
    while( !ccw2(P2[lRH2], P2[lOfRH2], P1[rOfLH2]) || !ccw2(P2[lOfRH2], P1[rOfLH2], P1[rLH2]) )
    {
        qDebug()<< "***P1.size()+ P2.size() = "<<P1.size()+ P2.size();
        while( !ccw2(P2[lRH2], P2[lOfRH2], P1[rOfLH2]) )
        {
            lOfRH2--;
            if(lOfRH2==-1) lOfRH2=P2.size()-1;

            if(lOfRH2==0) lRH2=P2.size()-1;//***
            else lRH2= lOfRH2-1;
        }


        while( !ccw2(P2[lOfRH2], P1[rOfLH2], P1[rLH2]) )
        {
            rOfLH2++;
            if(rOfLH2==P1.size()) rOfLH2=0;

            if(rOfLH2 == (P1.size()-1)) rLH2=0;//***
            else rLH2=rOfLH2+1 ;
        }

    }

    if(rOfLH > rOfLH2 )
    {
      for(int i=rOfLH2; i<=rOfLH; i++) result.push_back(P1[i]);
    }
    else
    {
       for(int j=rOfLH2 ; j<P1.size() ;j++) result.push_back(P1[j]);
       for(int k=0; k<=rOfLH  ;k++) result.push_back(P1[k]);
    }


    if(lOfRH2> lOfRH )
    {
      for(int m=lOfRH; m<=lOfRH2 ; m++)result.push_back( P2[m] );
    }
    else
    {
      for(int n=lOfRH ; n<P2.size() ; n++) result.push_back( P2[n] );
      for(int p=0; p<=lOfRH2; p++) result.push_back( P2[p] );
    }

    return result;
  }
  else
  {
      std::vector<CPoint> vps;
      for(unsigned int r=0; r<P1.size(); r++)
      {
        vps.push_back( P1[r] );
      }

      for(unsigned int g=0; g<P2.size(); g++)
      {
        vps.push_back( P2[g] );
      }

      qDebug()<< "jarvis(vps)--- vps.size()= "<<vps.size();
      qDebug()<< "jarvis(vps)--- vps.size()= "<<vps[3].getX()<<" "<<vps[3].getY();
      return jarvis(vps);

  }


}



std::vector<CPoint> MainWindow::divideConq(std::vector<CPoint> vertex )
{

    if(vertex.size()<=3) return vertex;

    int median= vertex.size()/2;
    qDebug()<< median;
    while( vertex[median-1].getX()== vertex[median].getX()) median++;

    std::vector<CPoint> S1, S2;

    for(int i=0; i<vertex.size(); i++)
    {
        if(i<median)
        {
            S1.push_back(vertex[i]);
        }
        else
        {
            S2.push_back(vertex[i]);
        }
    }

    std::vector<CPoint> R1, R2, Rf;
    R1 = divideConq(S1 );
    R2 = divideConq(S2 );

    Rf =Merge(R1, R2);

    return Rf;

}

#include "mainwindow.h"
#include "ui_mainwindow.h"

float f1(float x) {return sin(x);}
float df1(float x) {return cos(x);}
float ddf1(float x) {return -1*sin(x);}

float f2(float x){ return (x*x*x)+(x-1)*(x-1)+2; }
float df2(float x) {    return (3*x*x) - (2*x) - 2; }
float ddf2(float x) { return 6*x + 2; }

float f3(float x) { return (1/40)*(x-3)*(x-3)*(x-3) + 0.5*x*x; }
float df3(float x) { return (1/40)*(3*x*x + 22*x + 27); }
float ddf3(float x) {return 0.05 * (3*x+11); }

float f4(float x) {
    float a = ((1.0/40)*(x-15)*(x-15)*(x-15) + 0.5*(x-12)*(x-12) + 3);
    return a;
}
float df4(float x) { return 0.075*x*x - 1.25*x+4.875; }
float ddf4(float x) { return 0.15*x-1.25;}

float f5(float x) { return abs(x)-abs(x-1); }

//BS: f1,f2 ok
//f3, f4 - ?!

//

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mgv = new graphics();

    vector<Qt::GlobalColor> clrs={Qt::blue, Qt::red,Qt::green,Qt::black,Qt::darkBlue,Qt::darkCyan,Qt::darkGreen};


    //ui->gridLayout->addWidget(mgv);


    cout << "f4: " << f4(10.4999504) << endl;



    BisectionSolve* BS = new BisectionSolve(0.000001, 0.00001,10,11, f4, 10000);
    GoldenRatio* GR = new GoldenRatio(0.001, 0.0001, 10.2, 10.6, f4, 10000);
    FibMethod* FB = new FibMethod(10.2,10.6,0.0001,100,f4);
    Loman* LM = new Loman(10.2,10.6,0.0001,100,f4);
    NewtonMethod1d_extr* NMZ = new NewtonMethod1d_extr(0.001,10.2, f4,df4,ddf4,10000);
    //Strongin* SG = new Strongin(-1,1,0.0001,10000,f5,0.5);
    Strongin* SG = new Strongin(10.2,10.6,0.0001,10000,f4,0.5);

    vector<Solver1d*> solvs;
    solvs.push_back(BS);
    solvs.push_back(GR);
    solvs.push_back(FB);
    solvs.push_back(LM);
    solvs.push_back(NMZ);
    solvs.push_back(SG);

    /*
    auto res = BS->Solve();
    cout << "BS: " << res <<endl;
    cout << BS->stepCounter << endl;
    //delete BS;

    //solvs.push_back(BS);

    //GoldenRatio* GR = new GoldenRatio(0.001, 0.0001, 10.2, 10.6, f4, 10000);
    res = GR->Solve();
    cout << "GR: " << res << endl;
    cout << GR->stepCounter <<endl;
    //delete GR;

    //FibMethod* FB = new FibMethod(10.2,10.6,0.0001,100,f4);//(0.001, 0.0001, 10.2, 10.6, f4, 10000);
    res = FB->Solve();
    cout << "FB: " << res << endl;
    cout << FB->stepCounter <<endl;
    //delete FB;

    //Loman* LM = new Loman(10.2,10.6,0.0001,100,f4);
    res = LM->Solve();
    cout << "LM: " << res << endl;
    cout << LM->stepCounter <<endl;
    //delete LM;

    res = NMZ->Solve();
    cout << "NMZ: " << res << endl;
    cout << NMZ->stepCounter <<endl;
    */


    QwtPlot *d_plot = new QwtPlot( this );
    setCentralWidget(d_plot);
    d_plot->setTitle( "Comparing" ); // заголовок
    d_plot->setCanvasBackground( Qt::white ); // цвет фона

        // Параметры осей координат
    d_plot->setAxisTitle(QwtPlot::yLeft, "iter");
    d_plot->setAxisTitle(QwtPlot::xBottom, "err");



    for(int i = 0; i < solvs.size(); i++)
    {
        auto res = solvs[i]->Solve();
        cout << solvs[i]->stepCounter << endl;
        AddPlot___(d_plot, clrs[i], solvs[i]->delta_x);
    }

    /*
    QwtLegend *legend = new QwtLegend;
    legend->setDefaultItemMode( QwtLegendData::Checkable );

    QwtLegendData data;
    data.setValue(QwtLegendData::Role::TitleRole, QVariant("bisection"));
    QList<QwtLegendData> list;
    list << data;
    legend->updateLegend(QVariant(), list);

    QwtLegendData data1;
    data1.setValue(QwtLegendData::Role::TitleRole, QVariant("golden ratio"));
    QList<QwtLegendData> list1;
    list1 << data1;
    legend->updateLegend(QVariant(), list1);

    QwtLegendData data2;
    data2.setValue(QwtLegendData::Role::TitleRole, QVariant("fibonacci"));
    QList<QwtLegendData> list2;
    list2 << data2;
    legend->updateLegend(QVariant(), list2);

    QwtLegendData data3;
    data3.setValue(QwtLegendData::Role::TitleRole, QVariant("lomannaya"));
    QList<QwtLegendData> list3;
    list3 << data3;
    legend->updateLegend(QVariant(), list3);

    QwtLegendData data4;
    data4.setValue(QwtLegendData::Role::TitleRole, QVariant("kasatelnaya"));
    QList<QwtLegendData> list4;
    list4 << data4;
    legend->updateLegend(QVariant(), list4);

    d_plot->insertLegend( legend );
    */


        // Включить сетку
        // #include <qwt_plot_grid.h>
    QwtPlotGrid *grid = new QwtPlotGrid(); //
    grid->setMajorPen(QPen( Qt::gray, 2 )); // цвет линий и толщина
    grid->attach( d_plot ); // добавить сетку к полю графика




//    AddPlot___(d_plot, Qt::blue, BS->delta_x     );
//    AddPlot___(d_plot, Qt::red, GR->delta_x      );
//    AddPlot___(d_plot, Qt::green, FB->delta_x    );
//    AddPlot___(d_plot, Qt::black, LM->delta_x    );
//    AddPlot___(d_plot, Qt::darkBlue, NMZ->delta_x);



    /*
    QwtPlotCurve *curve1 = new QwtPlotCurve();
    QwtPlotCurve *curve2 = new QwtPlotCurve();
    QwtPlotCurve *curve3 = new QwtPlotCurve();
    //curve1->setTitle( "Demo Curve" );
    curve1->setPen(Qt::blue, 6);
    curve1->setRenderHint(QwtPlotItem::RenderAntialiased, true);

    curve2->setPen(Qt::red, 6);
    curve2->setRenderHint(QwtPlotItem::RenderAntialiased, true);

    curve3->setPen(Qt::green, 6);
    curve3->setRenderHint(QwtPlotItem::RenderAntialiased, true);


    //QwtSymbol *symbol1 = new QwtSymbol( QwtSymbol::Ellipse, //точки?
    //       QBrush( Qt::yellow ), QPen( Qt::red, 2 ), QSize( 8, 8 ) );
    //curve1->setSymbol( symbol1 );


    QPolygonF points1;
    QPolygonF points2;
    QPolygonF points3;

    for(int i = 0; i < BS->delta_x.size(); i++)
    {
        points1 << QPointF(BS->delta_x[i], i);
    }

    for(int i = 0; i < GR->delta_x.size(); i++)
    {
        points2 <<  QPointF(GR->delta_x[i], i);
    }

    for(int i = 0; i < FB->delta_x.size(); i++)
    {
        points3 <<  QPointF(FB->delta_x[i], i);
    }


           //    points1 << QPointF( 1.0, 1.0 ) // координаты x, y
           // << QPointF( 1.5, 2.0 ) << QPointF( 3.0, 2.0 )
           // << QPointF( 3.5, 3.0 ) << QPointF( 5.0, 3.0 );

    curve1->setSamples( points1 ); // ассоциировать набор точек с кривой
    curve1->attach( d_plot ); // отобразить кривую на графике

    curve2->setSamples( points2 ); // ассоциировать набор точек с кривой
    curve2->attach( d_plot ); // отобразить кривую на графике

    curve3->setSamples( points3 ); // ассоциировать набор точек с кривой
    curve3->attach( d_plot ); // отобразить кривую на графике
*/




    // Включить возможность приближения/удаления графика
    // #include <qwt_plot_magnifier.h>
    QwtPlotMagnifier *magnifier = new QwtPlotMagnifier(d_plot->canvas());
    // клавиша, активирующая приближение/удаление
    magnifier->setMouseButton(Qt::MidButton);


    // Включить возможность перемещения по графику
    // #include <qwt_plot_panner.h>
    QwtPlotPanner *d_panner = new QwtPlotPanner( d_plot->canvas() );
    // клавиша, активирующая перемещение
    d_panner->setMouseButton( Qt::RightButton );



    /*
    //BisectionSolve* BS = new BisectionSolve(0.1, 0.0001, 4, 6, f1, 10000);
    //auto res = BS->Solve();
    //cout << "BS: " << res <<endl;
    //mgv->FillToDraw1Vec(BS->delta_fx);
    //delete BS;
    //
    //GoldenRatio* GR = new GoldenRatio(0.1, 0.0001, 4, 6, f1, 10000);
    //res = GR->Solve();
    //cout << "GR: " << res <<endl;
    //mgv->FillToDraw1Vec(GR->delta_fx);
    //delete GR;
    //
    //float res;
    //
    //NewtonMethod1d_zero* NMz = new NewtonMethod1d_zero(0.001, 4.5, f1,df1,ddf1, 10000);
    //res = NMz->Solve();
    //cout << "NMz: "<< res << endl;
    //mgv->FillToDraw1Vec(NMz->delta_fx);
    //delete NMz;
    //
    //NewtonMethod1d_extr* NMe = new NewtonMethod1d_extr(0.001, 4.5, f1,df1,ddf1, 10000);
    //res = NMe->Solve();
    //cout << "NMe: " << res << endl;
    //mgv->FillToDraw1Vec(NMe->delta_fx);
    //delete NMe;
    */





}

MainWindow::~MainWindow()
{
    delete ui;
}


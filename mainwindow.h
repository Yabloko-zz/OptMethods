#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graphics.h"
#include "optmath.h"

#include <qwt_plot.h>
#include <qwt_plot_grid.h>

#include <qwt_legend.h>

#include <qwt_plot_curve.h>
#include <qwt_symbol.h>

#include <qwt_plot_magnifier.h>

#include <qwt_plot_panner.h>

#include <qwt_plot_picker.h>
#include <qwt_picker_machine.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void AddPlot___(QwtPlot *d_plot, Qt::GlobalColor clr, vector<float> pts)
    {
        QwtPlotCurve *curve = new QwtPlotCurve();

//        QwtLegendData data;
//        data.setValue(QwtLegendData::Role::TitleRole, QVariant("Outside temperature is 12C"));
//        QList<QwtLegendData> list;
//        list << data;


        //legend->setDefaultItemMode( QwtLegendData::Checkable );

        curve->setPen(clr, 6);
        curve->setRenderHint(QwtPlotItem::RenderAntialiased, true);
        curve->setLegendAttribute(curve->LegendShowLine);
        curve->setLegendAttribute(curve->LegendShowSymbol);

        QPolygonF points;

        for(int i = 0; i < pts.size(); i++)
        {
            points << QPointF(pts[i], i);
        }

        curve->setSamples( points ); // ассоциировать набор точек с кривой
        curve->attach( d_plot ); // отобразить кривую на графике
    }


private:
    Ui::MainWindow *ui;
    graphics *mgv;
};
#endif // MAINWINDOW_H

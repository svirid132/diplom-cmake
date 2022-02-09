#include "preloader.h"
#include "cmdchart.h"

#include <QDebug>
#include <QMainWindow>
#include <QChart>
#include <QValueAxis>
#include <QLineSeries>

#include <UI/mainwindow.h>
#include <UI/widgetchart.h>

QT_CHARTS_USE_NAMESPACE

QChart* initChartNimp_Glub(){
    QChart *chartNimp_Glub = new QChart();
//    chartNimp_Glub->setTitle("N и глубина");

//    chartNimp_Glub->addSeries(series);

    chartNimp_Glub->createDefaultAxes();
//    chartNimp_Glub->axes(Qt::Horizontal).first()->setRange(0, m_valueMax);
//    chartNimp_Glub->axes(Qt::Vertical).first()->setRange(0, m_valueCount);

//    QValueAxis *axisY = qobject_cast<QValueAxis*>(chartNimp_Glub->axes(Qt::Vertical).first());
//    Q_ASSERT(axisY);
//    axisY->setLabelFormat("%.1f  ");

    return chartNimp_Glub;
}

WidgetChart* initWidgetChart() {

    WidgetChart* widgetChart = new WidgetChart();

    QChart *chartNimp_Glub = initChartNimp_Glub();
    widgetChart->setChart(chartNimp_Glub);

    CmdChart* cmdChart = new CmdChart();
    cmdChart->setReceiver(chartNimp_Glub);

    QObject::connect(widgetChart, &WidgetChart::selectedFile, [=](float Lsh, float h, QString path) {
        cmdChart->update(Lsh, h, path);
    });

    return widgetChart;
}


void preloader(MainWindow& window) {
    QWidget* widgetChart = initWidgetChart();
    window.setCentralWidget(widgetChart);
}


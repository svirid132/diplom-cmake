#include "init-widget-chart.h"

#include <QLineSeries>
#include <QValueAxis>

QChart* initChartGlub_Nimp(){
    QChart *chartGlub_Nimp = new QChart();
    chartGlub_Nimp->legend()->hide();

    QValueAxis *axisX = new QValueAxis();
    QValueAxis *axisY = new QValueAxis();
    axisY->setLabelFormat("%i ");
    axisY->setTitleText("Колличество импульсов");
    axisX->setLabelsAngle(-90);
    axisX->setLabelFormat("%.2f ");
    axisX->setTitleText("Глубина, м");
    QFont font;
    font.setPixelSize(14);
    axisX->setLabelsFont(font);
    axisX->setRange(0, 30);
    axisY->setRange(0, 30);

    chartGlub_Nimp->addAxis(axisX, Qt::AlignBottom);
    chartGlub_Nimp->addAxis(axisY, Qt::AlignLeft);

    return chartGlub_Nimp;
}

QChart* initX1dh_NmaxdN0(){
    QChart *chartX1dh_NmaxdN0 = new QChart();
    chartX1dh_NmaxdN0->legend()->hide();

    QLineSeries *series = new QLineSeries(chartX1dh_NmaxdN0);
    auto points = MathLogic::getDefaultPoints(30);
    for (int i = 0; i < points.size(); ++i ){
        series->append(points[i]);
    }
    chartX1dh_NmaxdN0->addSeries(series);

    QValueAxis *axisX = new QValueAxis();
    QValueAxis *axisY = new QValueAxis();
    axisY->setLabelFormat("%i ");
    axisY->setTitleText("Nmax/N0");
    axisX->setLabelFormat("%.2f ");
    axisX->setTitleText("H1/h");
    QFont font;
    font.setPixelSize(14);
    axisX->setLabelsFont(font);
    axisX->setRange(0, points.last().x());
    axisY->setRange(0, points.last().y());
    chartX1dh_NmaxdN0->addAxis(axisX, Qt::AlignBottom);
    chartX1dh_NmaxdN0->addAxis(axisY, Qt::AlignLeft);

    series->attachAxis(axisX);
    series->attachAxis(axisY);
    return chartX1dh_NmaxdN0;
}

WidgetChart* initWidgetChart(CmdChart* const cmdChart) {
    WidgetChart* widgetChart = new WidgetChart();
    QChart *chartGlub_Nimp = initChartGlub_Nimp();
    QChart *chartX1dh_NmaxdN0 = initX1dh_NmaxdN0();
    widgetChart->setChart(chartGlub_Nimp);

    cmdChart->setReceiver(chartGlub_Nimp, chartX1dh_NmaxdN0);

    QObject::connect(widgetChart, &WidgetChart::clickedChartGlub_Nimp, widgetChart,  [=]() {
        widgetChart->setChart(chartGlub_Nimp);
    });
    QObject::connect(widgetChart, &WidgetChart::clickedChartX1dh_NmaxdN0, widgetChart, [=]() {
        widgetChart->setChart(chartX1dh_NmaxdN0);
    });

    return widgetChart;
}

#include "preloader.h"
#include "cmdchart.h"

#include <QDebug>
#include <QMainWindow>
#include <QChart>
#include <QValueAxis>
#include <QLineSeries>
#include <rawfile.h>
#include "math-logic.h"
#include "shared-func.h"

#include <UI/mainwindow.h>
#include <UI/widgetchart.h>

QT_CHARTS_USE_NAMESPACE

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

void initWidgetChart(MainWindow& window) {

    WidgetChart* widgetChart = new WidgetChart();
    MathLogic* logic = new MathLogic();

    QChart *chartGlub_Nimp = initChartGlub_Nimp();
    QChart *chartX1dh_NmaxdN0 = initX1dh_NmaxdN0();
    widgetChart->setChart(chartGlub_Nimp);

    CmdChart* cmdChart = new CmdChart();
    cmdChart->setReceiver(chartGlub_Nimp, chartX1dh_NmaxdN0);
    QObject::connect(widgetChart, &WidgetChart::executeAPI, widgetChart, [=, &window](float Lsh, float h, int period, QString path) {
        try {
            QVector<CountOverAmps> Nimp = RawFile::handleFile(path, period);
            logic->calc(Nimp, Lsh, h);

            float koefZap = logic->getKoefZap();
            CATEGORY category = logic->getCategory();
            QString categoryString = getCategoryString(category);
            widgetChart->setKoefZapCategory(koefZap, categoryString);

            cmdChart->update(logic);

        } catch (const ErrorFile& error) {
            widgetChart->errorFile();
            window.viewError(error.what());
        } catch (const ErrorPeriod& error) {
            widgetChart->errorPeriod();
            window.viewError(error.what());
        }
    });
    QObject::connect(widgetChart, &WidgetChart::clickedChartGlub_Nimp, widgetChart,  [=]() {
        widgetChart->setChart(chartGlub_Nimp);
    });
    QObject::connect(widgetChart, &WidgetChart::clickedChartX1dh_NmaxdN0, widgetChart, [=]() {
        widgetChart->setChart(chartX1dh_NmaxdN0);
    });

    //Test
    QVector<CountOverAmps> Nimp;
    Nimp <<
            CountOverAmps({588, 1}) << CountOverAmps({1700, 1}) << CountOverAmps({2500, 1}) << CountOverAmps({2000, 1}) << CountOverAmps({500, 1}) <<
            CountOverAmps({160, 1}) << CountOverAmps({12, 1}) << CountOverAmps({0, 1}) << CountOverAmps({0, 1}) << CountOverAmps({0, 1}) <<
            CountOverAmps({0, 1}) << CountOverAmps({230, 1}) << CountOverAmps({0, 1}) << CountOverAmps({0, 1}) << CountOverAmps({0, 1}) <<
            CountOverAmps({0, 1}) << CountOverAmps({0, 1}) << CountOverAmps({0, 1}) << CountOverAmps({0, 1}) << CountOverAmps({0, 1});
    logic->calc(Nimp, 2.5, 4.5);
    CATEGORY category = logic->getCategory();
    float koefZap = logic->getKoefZap();
    cmdChart->update(logic);
    widgetChart->setKoefZapCategory(koefZap, getCategoryString(category));

    window.setCentralWidget(widgetChart);
}


void preloader(MainWindow& window) {
    initWidgetChart(window);
}


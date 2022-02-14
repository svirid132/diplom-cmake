#include "preloader.h"
#include "cmdchart.h"

#include <QDebug>
#include <QMainWindow>
#include <QChart>
#include <QValueAxis>
#include <QLineSeries>
#include <rawfile.h>

#include <UI/mainwindow.h>
#include <UI/widgetchart.h>

QT_CHARTS_USE_NAMESPACE

QChart* initChartNimp_Glub(){
    QChart *chartNimp_Glub = new QChart();

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

    chartNimp_Glub->addAxis(axisX, Qt::AlignBottom);
    chartNimp_Glub->addAxis(axisY, Qt::AlignLeft);
//    chartNimp_Glub->setTitle("N и глубина");

//    chartNimp_Glub->addSeries(series);

//    chartNimp_Glub->createDefaultAxes();
//    chartNimp_Glub->axes(Qt::Horizontal).first()->setRange(0, m_valueMax);
//    chartNimp_Glub->axes(Qt::Vertical).first()->setRange(0, m_valueCount);

//    QValueAxis *axisY = qobject_cast<QValueAxis*>(chartNimp_Glub->axes(Qt::Vertical).first());
//    Q_ASSERT(axisY);
//    axisY->setLabelFormat("%.1f  ");

    return chartNimp_Glub;
}

void initWidgetChart(MainWindow& window) {

    WidgetChart* widgetChart = new WidgetChart();

    QChart *chartNimp_Glub = initChartNimp_Glub();
    widgetChart->setChart(chartNimp_Glub);

    CmdChart* cmdChart = new CmdChart();
    cmdChart->setReceiver(chartNimp_Glub);
    QObject::connect(widgetChart, &WidgetChart::executeAPI, [=, &window](float Lsh, float h, int period, QString path) {
        try {
            QVector<CountOverAmps> Nimp;
            if (false) {
                Nimp <<
                        CountOverAmps({588, 1}) << CountOverAmps({1700, 1}) << CountOverAmps({2500, 1}) << CountOverAmps({2000, 1}) << CountOverAmps({500, 1}) <<
                        CountOverAmps({160, 1}) << CountOverAmps({12, 1}) << CountOverAmps({0, 1}) << CountOverAmps({0, 1}) << CountOverAmps({0, 1}) <<
                        CountOverAmps({0, 1}) << CountOverAmps({230, 1}) << CountOverAmps({0, 1}) << CountOverAmps({0, 1}) << CountOverAmps({0, 1}) <<
                        CountOverAmps({0, 1}) << CountOverAmps({0, 1}) << CountOverAmps({0, 1}) << CountOverAmps({0, 1}) << CountOverAmps({0, 1});
            } else {
                Nimp = RawFile::handleFile(path, period);
            }
            cmdChart->update(Nimp, Lsh, h);
        } catch (const ErrorFile& error) {
            widgetChart->errorFile();
            window.viewError(error.what());
        } catch (const ErrorPeriod& error) {
            widgetChart->errorPeriod();
            window.viewError(error.what());
        }
    });

    //Test
    QVector<CountOverAmps> Nimp;
    if (true) {
        Nimp <<
                CountOverAmps({588, 1}) << CountOverAmps({1700, 1}) << CountOverAmps({2500, 1}) << CountOverAmps({2000, 1}) << CountOverAmps({500, 1}) <<
                CountOverAmps({160, 1}) << CountOverAmps({12, 1}) << CountOverAmps({0, 1}) << CountOverAmps({0, 1}) << CountOverAmps({0, 1}) <<
                CountOverAmps({0, 1}) << CountOverAmps({230, 1}) << CountOverAmps({0, 1}) << CountOverAmps({0, 1}) << CountOverAmps({0, 1}) <<
                CountOverAmps({0, 1}) << CountOverAmps({0, 1}) << CountOverAmps({0, 1}) << CountOverAmps({0, 1}) << CountOverAmps({0, 1});
    } else {
        Nimp = RawFile::handleFile("path", 1);
    }
    cmdChart->update(Nimp, 2.5, 4.5);

    window.setCentralWidget(widgetChart);
}


void preloader(MainWindow& window) {
    initWidgetChart(window);
}


#include "cmdchart.h"
#include "math-logic.h"
#include "rawfile.h"
#include <QGraphicsLayout>

#include <QLegendMarker>
#include <QLineSeries>
#include <QValueAxis>

CmdChart::CmdChart()
{

}

void CmdChart::setReceiver(QChart *chartNimp_Glub)
{
    this->chartNimp_Glub = chartNimp_Glub;
}

void CmdChart::update(float Lsh, float h, QString filePath) {
    QVector<CountOverAmps> Nimp;
    if (true) {
        Nimp <<
                CountOverAmps({588, 1}) << CountOverAmps({1700, 1}) << CountOverAmps({2500, 1}) << CountOverAmps({2000, 1}) << CountOverAmps({500, 1}) <<
                CountOverAmps({160, 1}) << CountOverAmps({12, 1}) << CountOverAmps({0, 1}) << CountOverAmps({0, 1}) << CountOverAmps({0, 1}) <<
                CountOverAmps({0, 1}) << CountOverAmps({230, 1}) << CountOverAmps({0, 1}) << CountOverAmps({0, 1}) << CountOverAmps({0, 1}) <<
                CountOverAmps({0, 1}) << CountOverAmps({0, 1}) << CountOverAmps({0, 1}) << CountOverAmps({0, 1}) << CountOverAmps({0, 1});
    } else {
        Nimp = RawFile::handleFile(filePath, 1);
    }
    QVector<QPointF> Nimp_Glub = MathLogic::getNimp_Glub(Nimp, Lsh);

    chartNimp_Glub->removeAllSeries();
    QLineSeries *series = new QLineSeries(chartNimp_Glub);
    for (int i = 0; i < Nimp_Glub.size(); ++i) {
        series->append(Nimp_Glub[i]);
    }
//    series->setName("График");
//    series->setPointLabelsVisible(true);    // is false by default
//    series->setPointLabelsColor(Qt::black);
//    series->setPointLabelsFormat("@yPoint");
    qDebug() << "Lsh" << Lsh;
    chartNimp_Glub->addSeries(series);
    chartNimp_Glub->createDefaultAxes();
    QValueAxis *axisY = qobject_cast<QValueAxis*>(chartNimp_Glub->axes(Qt::Vertical).first());
    axisY->setLabelFormat("%i ");
    axisY->setTitleText("Колличество импульсов");
    QValueAxis *axisX = qobject_cast<QValueAxis*>(chartNimp_Glub->axes(Qt::Horizontal).first());
    axisX->setLabelsAngle(-90);
    axisX->setTickCount(20);
    axisX->setLabelFormat("%.2f ");
    axisX->setTitleText("Глубина, м");
    qDebug() << axisX->tickType();

//    chartNimp_Glub->layout()->setContentsMargins(-10, -10, -10, -10);
//    chartNimp_Glub->setBackgroundRoundness(0);
//    chartNimp_Glub->legend()->markers(series).at(0)->setVisible(false);
    chartNimp_Glub->legend()->hide();
}

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

void CmdChart::setReceiver(QChart *chartGlub_Nimp)
{
    this->chartGlub_Nimp = chartGlub_Nimp;
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

    handleChartGlub_Nimp(Nimp, Lsh);
}

void CmdChart::handleChartGlub_Nimp(const QVector<CountOverAmps> &Nimp, float Lsh)
{
    QVector<QPointF> Nimp_Glub = MathLogic::getGlub_Nimp(Nimp, Lsh);

    chartGlub_Nimp->removeAllSeries();
    QLineSeries *series = new QLineSeries(chartGlub_Nimp);
    for (int i = 0; i < Nimp_Glub.size(); ++i) {
        series->append(Nimp_Glub[i]);
    }
    //показ значений точек
//    series->setName("График");
//    series->setPointLabelsVisible(true);    // is false by default
//    series->setPointLabelsColor(Qt::black);
//    series->setPointLabelsFormat("@yPoint");
    chartGlub_Nimp->addSeries(series);
    chartGlub_Nimp->createDefaultAxes();
    QValueAxis *axisY = qobject_cast<QValueAxis*>(chartGlub_Nimp->axes(Qt::Vertical).first());
    Q_ASSERT(axisY);
    axisY->setLabelFormat("%i ");
    axisY->setTitleText("Колличество импульсов");
    QValueAxis *axisX = qobject_cast<QValueAxis*>(chartGlub_Nimp->axes(Qt::Horizontal).first());
    Q_ASSERT(axisX);
    axisX->setLabelsAngle(-90);
    axisX->setTickCount(Nimp.size() > 20 ? 20 : Nimp.size());
    axisX->setLabelFormat("%.2f ");
    axisX->setTitleText("Глубина, м");
    QFont font;
    font.setPixelSize(14);
    axisX->setLabelsFont(font);

    chartGlub_Nimp->legend()->hide();
}

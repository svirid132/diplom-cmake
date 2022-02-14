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

void CmdChart::update(const QVector<CountOverAmps>& Nimp, float Lsh, float h) {
    handleChartGlub_Nimp(Nimp, Lsh);
}

void CmdChart::handleChartGlub_Nimp(const QVector<CountOverAmps> &Nimp, float Lsh)
{
    QVector<QPointF> Glub_Nimp = MathLogic::getGlub_Nimp(Nimp, Lsh);

    chartGlub_Nimp->removeAllSeries();
    QLineSeries *series = new QLineSeries(chartGlub_Nimp);
    QPointF screenPoint = {0, 0};
    qDebug() << "Glub_Nimp[i]";
    for (int i = 0; i < Glub_Nimp.size(); ++i) {
        series->append(Glub_Nimp[i]);
        if (screenPoint.y() < Glub_Nimp[i].y()) screenPoint.setY(Glub_Nimp[i].y());
        qDebug() << Glub_Nimp[i];
    }
    screenPoint.setX(Glub_Nimp.last().x());
    //показ значений точек
//    series->setName("График");
//    series->setPointLabelsVisible(true);    // is false by default
//    series->setPointLabelsColor(Qt::black);
//    series->setPointLabelsFormat("@yPoint");
    chartGlub_Nimp->addSeries(series);

    QValueAxis *axisY = qobject_cast<QValueAxis*>(chartGlub_Nimp->axes(Qt::Vertical).first());
    Q_ASSERT(axisY);
    axisY->setRange(0, screenPoint.y());
    series->attachAxis(axisY);
    QValueAxis *axisX = qobject_cast<QValueAxis*>(chartGlub_Nimp->axes(Qt::Horizontal).first());
    Q_ASSERT(axisX);
    series->attachAxis(axisX);
    axisX->setRange(0, screenPoint.x());
    axisX->setTickCount(Nimp.size() > 20 ? 20 : Nimp.size());

    chartGlub_Nimp->legend()->hide();
}

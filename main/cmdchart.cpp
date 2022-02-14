#include "cmdchart.h"
#include "math-logic.h"
#include "rawfile.h"
#include <QGraphicsLayout>

#include <QLegendMarker>
#include <QLineSeries>
#include <QScatterSeries>
#include <QValueAxis>
#include "shared-func.h"

CmdChart::CmdChart() :
    criticalSeriesPoint(nullptr)
{

}

void CmdChart::setReceiver(QChart *chartGlub_Nimp, QChart * chartX1dh_NmaxdN0)
{
    this->chartGlub_Nimp = chartGlub_Nimp;
    this->chartX1dh_NmaxdN0 = chartX1dh_NmaxdN0;
}

void CmdChart::update(const QVector<CountOverAmps>& Nimp, float Lsh, float h, CATEGORY category) {
    handleChartGlub_Nimp(Nimp, Lsh);
    handleX1dh_NmaxdN0(Nimp, Lsh, h, category);
}

void CmdChart::handleX1dh_NmaxdN0(const QVector<CountOverAmps>& Nimp, float Lsh, float h, CATEGORY category){
    QPointF criticalPoint = MathLogic::getCriticalPoint(Nimp, h, Lsh);
    if (criticalSeriesPoint) {
        this->chartX1dh_NmaxdN0->removeSeries(criticalSeriesPoint);
    }
    QLineSeries* defaultLine = qobject_cast<QLineSeries*>(chartX1dh_NmaxdN0->series().first());
    QColor color;
    switch(category) {
    case CATEGORY::PERILOUSLY:
        color = QColor(Qt::red);
        break;
    case CATEGORY::SAFELY:
        const QString green = "#008000";
        color = QColor(green);
        break;
    }

    defaultLine->setColor(color);

    criticalSeriesPoint = new QScatterSeries(chartX1dh_NmaxdN0);
    criticalSeriesPoint->append(criticalPoint);
    criticalSeriesPoint->setColor(color);
    criticalSeriesPoint->setMarkerSize(10);
    criticalSeriesPoint->setPointLabelsVisible(true);
    QString string = getCategoryString(category);
    criticalSeriesPoint->setPointLabelsFormat(string);
    this->chartX1dh_NmaxdN0->addSeries(criticalSeriesPoint);
    QValueAxis *axisY = qobject_cast<QValueAxis*>(chartX1dh_NmaxdN0->axes(Qt::Vertical).first());
    Q_ASSERT(axisY);
    criticalSeriesPoint->attachAxis(axisY);
    QValueAxis *axisX = qobject_cast<QValueAxis*>(chartX1dh_NmaxdN0->axes(Qt::Horizontal).first());
    Q_ASSERT(axisX);
    criticalSeriesPoint->attachAxis(axisX);
}

void CmdChart::handleChartGlub_Nimp(const QVector<CountOverAmps> &Nimp, float Lsh)
{
    QVector<QPointF> Glub_Nimp = MathLogic::getGlub_Nimp(Nimp, Lsh);

    chartGlub_Nimp->removeAllSeries();
    QLineSeries *series = new QLineSeries(chartGlub_Nimp);
    QPointF screenPoint = {0, 0};
    for (int i = 0; i < Glub_Nimp.size(); ++i) {
        series->append(Glub_Nimp[i]);
        if (screenPoint.y() < Glub_Nimp[i].y()) screenPoint.setY(Glub_Nimp[i].y());
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
}

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

void CmdChart::update(MathLogic *const logic) {
    handleChartGlub_Nimp(logic);
    handleX1dh_NmaxdN0(logic);
}

void CmdChart::handleX1dh_NmaxdN0(MathLogic *const logic){
    QPointF criticalPoint = logic->getCriticalPoint();
    if (criticalSeriesPoint) {
        this->chartX1dh_NmaxdN0->removeSeries(criticalSeriesPoint);
    }
    QLineSeries* defaultLine = qobject_cast<QLineSeries*>(chartX1dh_NmaxdN0->series().at(0));
    QColor color;
    switch(logic->getCategory()) {
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
    QString string = getCategoryString(logic->getCategory());
    criticalSeriesPoint->setPointLabelsFormat(string);
    this->chartX1dh_NmaxdN0->addSeries(criticalSeriesPoint);
    QValueAxis *axisY = qobject_cast<QValueAxis*>(chartX1dh_NmaxdN0->axes(Qt::Vertical).at(0));
    Q_ASSERT(axisY);
    criticalSeriesPoint->attachAxis(axisY);
    QValueAxis *axisX = qobject_cast<QValueAxis*>(chartX1dh_NmaxdN0->axes(Qt::Horizontal).at(0));
    Q_ASSERT(axisX);
    criticalSeriesPoint->attachAxis(axisX);
}

void CmdChart::handleChartGlub_Nimp(MathLogic *const logic)
{
    QVector<CountOverAmps> Nimp = logic->getNimp();
    QVector<QPointF> Glub_Nimp = logic->getGlub_Nimp();

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

    QValueAxis *axisY = qobject_cast<QValueAxis*>(chartGlub_Nimp->axes(Qt::Vertical).at(0));
    Q_ASSERT(axisY);
    axisY->setRange(0, screenPoint.y());
    series->attachAxis(axisY);
    QValueAxis *axisX = qobject_cast<QValueAxis*>(chartGlub_Nimp->axes(Qt::Horizontal).at(0));
    Q_ASSERT(axisX);
    series->attachAxis(axisX);
    axisX->setRange(0, screenPoint.x());
    axisX->setTickCount(Nimp.size() > 20 ? 20 : Nimp.size());
}

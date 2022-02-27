#ifndef HANDLERCHART_H
#define HANDLERCHART_H

#include <QList>
#include <QMap>
#include <QPointF>

enum CHART_NUMBER {
    first,
    second
};

struct AxisChart {
    QString x = "";
    QString y = "";
};

class HandlerChart
{
public:
    HandlerChart();
    void setRawData(const QString& rawData);
    void appendChart(QList<QPointF> chart, CHART_NUMBER chartNumber, const QString& namePoint = "");
    QString handleCharts();

private:
    QString rawData;
    QMap<CHART_NUMBER, AxisChart> charts;
    QString namePoint;
};

#endif // HANDLERCHART_H

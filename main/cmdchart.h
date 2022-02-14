#ifndef CMDCHART_H
#define CMDCHART_H

#include <API-var.h>
#include <QChart>
#include <QScatterSeries>
#include "math-var.h"
QT_CHARTS_USE_NAMESPACE

class CmdChart
{
public:
    CmdChart();

    void setReceiver(QChart *chartGlub_Nimp, QChart *chartX1dh_NmaxdN0);
    void update(const QVector<CountOverAmps>& Nimp, float Lsh, float h, CATEGORY category);

private:
    QChart* chartGlub_Nimp;
    QChart* chartX1dh_NmaxdN0;
    void handleChartGlub_Nimp(const QVector<CountOverAmps>& Nimp, float Lsh);
    void handleX1dh_NmaxdN0(const QVector<CountOverAmps>& Nimp, float Lsh, float h, CATEGORY category);
    QScatterSeries* criticalSeriesPoint;
};

#endif // CMDCHART_H

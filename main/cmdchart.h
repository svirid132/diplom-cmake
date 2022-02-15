#ifndef CMDCHART_H
#define CMDCHART_H

#include <API-var.h>
#include <QChart>
#include <QScatterSeries>
#include <math-logic.h>
#include "math-var.h"
QT_CHARTS_USE_NAMESPACE

class CmdChart
{
public:
    CmdChart();

    void setReceiver(QChart *chartGlub_Nimp, QChart *chartX1dh_NmaxdN0);
    void update(MathLogic *const logic);

private:
    QChart* chartGlub_Nimp;
    QChart* chartX1dh_NmaxdN0;
    void handleChartGlub_Nimp(MathLogic *const logic);
    void handleX1dh_NmaxdN0(MathLogic *const logic);
    QScatterSeries* criticalSeriesPoint;
};

#endif // CMDCHART_H

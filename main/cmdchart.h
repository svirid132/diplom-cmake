#ifndef CMDCHART_H
#define CMDCHART_H

#include <API-var.h>
#include <QChart>
QT_CHARTS_USE_NAMESPACE

class CmdChart
{
public:
    CmdChart();

    void setReceiver(QChart* chartNimp_Glub);
    void update(float Lsh, float h, QString filePath);

private:
    QChart* chartGlub_Nimp;
    void handleChartGlub_Nimp(const QVector<CountOverAmps>& Nimp, float Lsh);
};

#endif // CMDCHART_H
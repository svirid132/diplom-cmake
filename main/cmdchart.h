#ifndef CMDCHART_H
#define CMDCHART_H

#include <QChart>
QT_CHARTS_USE_NAMESPACE

class CmdChart
{
public:
    CmdChart();

    void setReceiver(QChart* chartNimp_Glub);
    void update(float Lsh, float h, QString filePath);

private:
    QChart* chartNimp_Glub;
};

#endif // CMDCHART_H

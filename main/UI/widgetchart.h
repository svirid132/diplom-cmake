#ifndef WIDGETCHART_H
#define WIDGETCHART_H

#include <QWidget>
#include <QChartView>

QT_CHARTS_USE_NAMESPACE

class WidgetChart : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetChart(QWidget *parent = nullptr);
    void setChart(QChart* chart);

private:
    QChartView *chartView;
signals:
    void clickedChartGlub_Nimp();
    void clickedChartX1dh_NmaxdN0();
};

#endif // WIDGETCHART_H

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
signals:
    void selectedFile(float Lsh, float h, QString path);

private slots:
    void openFile();

private:
    float Lsh;
    float h;
    QChartView *chartView;
};

#endif // WIDGETCHART_H

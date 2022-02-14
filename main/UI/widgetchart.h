#ifndef WIDGETCHART_H
#define WIDGETCHART_H

#include <QWidget>
#include <QChartView>
#include <QSpinBox>
#include <QLabel>

QT_CHARTS_USE_NAMESPACE

class WidgetChart : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetChart(QWidget *parent = nullptr);
    void errorFile();
    void errorPeriod();

    void setChart(QChart* chart);
signals:
    void executeAPI(float Lsh, float h, int period, QString path);

private slots:
    void openFile();

private:
    float Lsh;
    float h;
    QChartView *chartView;
    bool isError;
    QString filenameAPI;
    int period;

    QSpinBox* spinBoxPeriod;
    QLabel* labelFile;

    void setLabelFilename(const QString& filename);
};

#endif // WIDGETCHART_H

#ifndef WIDGETMAIN_H
#define WIDGETMAIN_H

#include <QWidget>
#include <QSpinBox>
#include <QLabel>
#include <QFormLayout>

class WidgetMain : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetMain(QWidget *parent = nullptr);
    void errorFile();
    void errorPeriod();
    void setKoefZap(float koefZap);

    void setKoefZapCategory(float koefZap, QString category);
    void setWidget(QWidget* widget);
signals:
    void executeAPI(float Lsh, float h, int period, QString path);

private slots:
    void openFile();

private:
    float Lsh;
    float h;
    bool isError;
    QString filenameAPI;
    int period;

    QSpinBox* spinBoxPeriod;
    QLabel* labelFile;
    QLabel* labelCategory;
    QLabel* labelKoefZap;

    QHBoxLayout* layout;

    void setLabelFilename(const QString& filename);
    void fillLayoutPanel(QFormLayout *const layout);
};

#endif // WIDGETMAIN_H

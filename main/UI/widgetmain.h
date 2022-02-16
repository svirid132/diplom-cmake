#ifndef WIDGETMAIN_H
#define WIDGETMAIN_H

#include <QWidget>
#include <QSpinBox>
#include <QLabel>
#include <QFormLayout>
#include <QPushButton>
#include <QGroupBox>

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
    void setEnabledXMLbtn(bool flag);
    void setEnabledPanel(bool flag);
signals:
    void executeAPI(float Lsh, float h, int period, QString path);
    void clickedSaveXML(bool);

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
    QPushButton* XMLbtn;
    QWidget* secondWidget;
    QWidget* leftPanel;
    QList<QWidget*> blockingWdgs;

    QHBoxLayout* layout;

    void setLabelFilename(const QString& filename);
    void fillLayoutPanel(QFormLayout *const layout);
};

#endif // WIDGETMAIN_H

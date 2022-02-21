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
    void setEnabledPanel(bool flag);
    void successChange();
signals:
    void executeAPI(float Lsh, float h, int period, QString path);
    void clickedSaveXML(bool);

private slots:
    void openFile();

private:
    struct Result {
        float Lsh;
        float h;
        int period;
    } successResult, middleResult;

    bool isError;
    QString filenameAPI;

    QSpinBox* spinBoxPeriod;
    QLabel* labelFile;
    QLabel* labelCategory;
    QLabel* labelKoefZap;
    QPushButton* XMLbtn;
    QWidget* secondWidget;
    QWidget* leftPanel;
    QList<QWidget*> blockingWdgs;

    QHBoxLayout* layout;

    const QString preChange = "(*) ";
    const QString strLsh = "Lsh:";
    const QString strh = "h:";
    const QString strPeriod = "Period(sec):";
    const QString skip = "      ";

    //Label
    QLabel* labelsLsh;
    QLabel* labelsh;
    QLabel* labelPeriod;
    //labelFile

    void setEnabledXMLbtn(bool flag);
    void setLabelFilename(const QString &path, bool preChange = true);
    void fillLayoutPanel(QFormLayout *const layout);
    bool isChange();
    void updateEnabledXMLbtn();
};

#endif // WIDGETMAIN_H

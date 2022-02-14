#include "widgetchart.h"

#include <QChartView>
#include <QDebug>
#include <QDialog>
#include <QFileDialog>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QTextEdit>
#include <qchartview.h>
#include <qchartview.h>
#include "global-var.h"

WidgetChart::WidgetChart(QWidget *parent)
    : QWidget{parent},
      Lsh(1),
      h(1),
      period(1),
      chartView(new QChartView),
      isError(false)
{
    QGridLayout *layout = new QGridLayout;
    layout->setVerticalSpacing(15);

    QLabel* labelsLsh = new QLabel(tr("Lsh:"));
    QLabel* labelsh = new QLabel(tr("h:"));
    layout->addWidget(labelsLsh, 0, 0);
    layout->addWidget(labelsh, 1, 0);
    QDoubleSpinBox* spinBoxLsh = new QDoubleSpinBox;
    QDoubleSpinBox* spinBoxh = new QDoubleSpinBox;
    spinBoxLsh->setMinimum(1);
    spinBoxh->setMinimum(1);
    layout->addWidget(spinBoxLsh, 0, 1);
    layout->addWidget(spinBoxh, 1, 1);
    connect(spinBoxLsh, QOverload<double>::of(&QDoubleSpinBox::valueChanged), [=](double value) {
        Lsh = float(value);
    });
    connect(spinBoxh, QOverload<double>::of(&QDoubleSpinBox::valueChanged), [=](double value) {
        h = float(value);
    });

    QPushButton* selectButton = new QPushButton("Обзор");
    connect(selectButton, &QPushButton::clicked, this, &WidgetChart::openFile);
    labelFile = new QLabel();
    labelFile->setSizePolicy(QSizePolicy(QSizePolicy::Ignored, QSizePolicy::Minimum));
    QVBoxLayout* vertical = new QVBoxLayout();
    vertical->addWidget(labelFile);
    vertical->addWidget(selectButton);
    QGroupBox* groupBox = new QGroupBox(this);
    groupBox->setTitle("Выбор файла");
    groupBox->setLayout(vertical);
    layout->addWidget(groupBox, 2, 0, 1, 2);

    QLabel* labelPeriod = new QLabel(tr("Period(sec):"));
    layout->addWidget(labelPeriod, 3, 0);
    spinBoxPeriod = new QSpinBox;
    spinBoxPeriod->setMinimum(1);
    connect(spinBoxPeriod, QOverload<int>::of(&QSpinBox::valueChanged),[=](int num){
        spinBoxPeriod->setStyleSheet("");
        period = num;
    });
    layout->addWidget(spinBoxPeriod, 3, 1);

    QVBoxLayout* boxLayout = new QVBoxLayout();
    labelKoefZap = new QLabel("Коэф.зап:");
    boxLayout->addWidget(labelKoefZap);
    boxLayout->addSpacing(5);
    labelCategory = new QLabel("Категоря:");
    boxLayout->addWidget(labelCategory);
    layout->addLayout(boxLayout, 4, 0, 1, 1);

    QPushButton* executeButton = new QPushButton("Выполнить");
    layout->setRowMinimumHeight(5, 10);
    layout->addWidget(executeButton, 6, 0, 1, 2);
    connect(executeButton, &QPushButton::clicked, [=](){
        emit executeAPI(Lsh, h, period, filenameAPI);
    });

    QHBoxLayout* hlayout = new QHBoxLayout();
    QPushButton* btn = new QPushButton("График 1");
    QPushButton* btn1 = new QPushButton("График 2");
    connect(btn, &QPushButton::clicked, this, &WidgetChart::clickedChartGlub_Nimp);
    connect(btn1, &QPushButton::clicked, this, &WidgetChart::clickedChartX1dh_NmaxdN0);
    hlayout->addSpacing(250);
    hlayout->addWidget(btn);
    hlayout->addWidget(btn1);
    QVBoxLayout* chartLayout = new QVBoxLayout();
    chartLayout->addWidget(chartView);
    chartLayout->addLayout(hlayout);
    layout->addLayout(chartLayout, 0, 2, 10, 1);

    this->setLayout(layout);
}

void WidgetChart::errorFile()
{
    labelFile->setStyleSheet("background-color: red; padding: 2px;");
}

void WidgetChart::errorPeriod()
{
    spinBoxPeriod->setStyleSheet("background-color: red");
}

void WidgetChart::setKoefZapCategory(float koefZap, QString category)
{
    QString num = tr("Коэф.зап: ") + QString::number(koefZap);
    QString fullCategory = "Категоря: " + category;
    labelKoefZap->setText(num);
    labelCategory->setText(fullCategory);
}


void WidgetChart::setLabelFilename(const QString& path)
{
    int positionFilename = path.lastIndexOf("/") + 1;
    QString filename = path.mid(positionFilename);
    const int wordWidth = 15;
    const int countPath = filename.size() / wordWidth;
    for (int i = 0; i < countPath; ++i) {
        filename.insert(wordWidth * (i + 1) + i, '\n');
    }
    labelFile->setStyleSheet("padding: 2px;");
    labelFile->setText(filename);
}

void WidgetChart::openFile()
{
    QFileDialog dialog;
    const QString filter = "Raw files (*.raw)";
    dialog.setNameFilter(filter);
    int width = 500;
    int height = 400;
    dialog.setGeometry(
                WIDTH_SCREEN / 2 - width / 2,
                HEIGHT_SCREEN / 2 - height / 2,
                width,
                height);
    if (dialog.exec()) {
        filenameAPI = dialog.selectedFiles().at(0);
        setLabelFilename(filenameAPI);
    }
}

void WidgetChart::setChart(QChart* chart) {
    chartView->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
}

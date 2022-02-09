#include "widgetchart.h"

#include <QChartView>
#include <QDebug>
#include <QDialog>
#include <QFileDialog>
#include <QGridLayout>
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
      chartView(new QChartView)
{
    QGridLayout *layout = new QGridLayout;

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
    connect(spinBoxLsh, QOverload<double>::of(&QDoubleSpinBox::valueChanged), [=](double value) {
        h = float(value);
    });

    QPushButton* button = new QPushButton("Обзор");
    connect(button, &QPushButton::clicked, this, &WidgetChart::openFile);
    layout->addWidget(button, 2, 1);

    layout->addWidget(chartView, 0, 2, 4, 1);

    layout->setColumnStretch(1, 10);
    layout->setColumnStretch(2, 60);

    this->setLayout(layout);
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
        QString fileName = dialog.selectedFiles().at(0);
        emit selectedFile(Lsh, h, fileName);
    }
    if(true) emit selectedFile(2.5, 4.5, "fileName");
}

void WidgetChart::setChart(QChart* chart) {
    chartView->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
}

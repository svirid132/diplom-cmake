#include "widgetchart.h"

#include <QHBoxLayout>
#include <QPushButton>

WidgetChart::WidgetChart(QWidget *parent) :
    QWidget(parent),
    chartView(new QChartView)
{
    QHBoxLayout* hlayout = new QHBoxLayout();
    QPushButton* btn = new QPushButton("График 1");
    QPushButton* btn1 = new QPushButton("График 2");
    connect(btn, &QPushButton::clicked, this, &WidgetChart::clickedChartGlub_Nimp);
    connect(btn1, &QPushButton::clicked, this, &WidgetChart::clickedChartX1dh_NmaxdN0);
    hlayout->setSpacing(5);
    hlayout->addSpacing(250);
    hlayout->addWidget(btn);
    hlayout->addWidget(btn1);

    QVBoxLayout* chartLayout = new QVBoxLayout();
    chartLayout->addWidget(chartView);
    chartLayout->addLayout(hlayout);

    this->setLayout(chartLayout);
    chartLayout->setSpacing(0);
    chartLayout->setMargin(0);
//    this->setStyleSheet("background-color: red");
}

void WidgetChart::setChart(QChart* chart) {
    chartView->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
}

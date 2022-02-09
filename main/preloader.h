#ifndef PRELOADER_H
#define PRELOADER_H

#include "cmdchart.h"

#include <QDebug>
#include <QMainWindow>
#include <QChart>
#include <QValueAxis>
#include <QLineSeries>

#include <UI/mainwindow.h>
#include <UI/widgetchart.h>

QT_CHARTS_USE_NAMESPACE

QChart* initChartNimp_Glub();

WidgetChart* initWidgetChart();

void preloader(MainWindow& window);


#endif // PRELOADER_H

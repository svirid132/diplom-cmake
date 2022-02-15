#include "preloader.h"
#include "cmdchart.h"

#include <QDebug>
#include <QMainWindow>
#include <QChart>
#include <QValueAxis>
#include <QLineSeries>
#include <rawfile.h>
#include "math-logic.h"
#include "shared-func.h"

#include <UI/mainwindow.h>
#include <UI/widgetchart.h>
#include <UI/widgetmain.h>

#include "preloader/init-widget-chart.h"
#include "preloader/init-widget-main.h"

void preloader(MainWindow& window) {
    CmdChart* cmdChart = new CmdChart();

    WidgetChart* widgetChart = initWidgetChart(cmdChart);
    WidgetMain* widgetMain = initWidgetMain(window, widgetChart, cmdChart);

    window.setCentralWidget(widgetMain);
}


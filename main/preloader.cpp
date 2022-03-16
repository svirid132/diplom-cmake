#include "preloader.h"

#include <preloader/InitDialogCommission.h>
#include <QtCore/QDir>
#include <preloader/FileSystem.h>
#include <preloader/InitDialogConverter.h>

#include "UI/widget-xml.h"

#include "preloader/init-widget-chart.h"
#include "preloader/init-widget-main.h"


void preloader(MainWindow& window) {
    //FileSystems
    FileSystems::mkdirDirFiles();

    //share logic
    CmdChart* cmdChart = new CmdChart();

    //init widget
    WidgetChart* widgetChart = initWidgetChart(cmdChart);
    WidgetXML* widgetXML = new WidgetXML();
    WidgetMain* widgetMain = initWidgetMain(window, widgetXML, widgetChart, cmdChart);

    //init dialog
    auto openDialogCommission = initDialogCommission(window);
    auto openDialogConverter = initDialogConverter(window, FileSystems::dirFiles);

    //set widget and diloag
    window.setCentralWidget(widgetMain);
    window.setDialogCommission(openDialogCommission);
    window.setDialogConverter(openDialogConverter);
}


#ifndef INITWIDGETMAIN_H
#define INITWIDGETMAIN_H

#include <UI/WidgetMain.h>
#include <UI/mainwindow.h>
#include <UI/widgetchart.h>
#include <CmdChart.h>


WidgetMain* initWidgetMain(MainWindow& window, WidgetChart* widgetChart, CmdChart* const cmdChart);

#endif // INITWIDGETMAIN_H

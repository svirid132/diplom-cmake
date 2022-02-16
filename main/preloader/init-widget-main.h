#ifndef INITWIDGETMAIN_H
#define INITWIDGETMAIN_H

#include <UI/WidgetMain.h>
#include <UI/mainwindow.h>
#include <UI/widget-xml.h>
#include <UI/widgetchart.h>
#include <CmdChart.h>


WidgetMain* initWidgetMain(MainWindow& window, WidgetXML* widgetXML, WidgetChart* widgetChart, CmdChart* const cmdChart);

#endif // INITWIDGETMAIN_H

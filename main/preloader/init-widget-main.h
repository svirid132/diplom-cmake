#ifndef INITWIDGETMAIN_H
#define INITWIDGETMAIN_H

#include <UI/mainwindow.h>
#include <UI/widget-xml.h>
#include <UI/widgetchart.h>
#include <UI/widgetmain.h>
#include <cmdchart.h>

WidgetMain* initWidgetMain(MainWindow& window, WidgetXML* widgetXML, WidgetChart* widgetChart, CmdChart* const cmdChart);

#endif // INITWIDGETMAIN_H

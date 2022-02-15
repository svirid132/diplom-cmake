#include "init-widget-main.h"
#include "shared-func.h"
#include <rawfile.h>

void test(MathLogic *const logic, CmdChart *const cmdChart, WidgetMain *const widgetMain) {
    QVector<CountOverAmps> Nimp;
    Nimp <<
            CountOverAmps({588, 1}) << CountOverAmps({1700, 1}) << CountOverAmps({2500, 1}) << CountOverAmps({2000, 1}) << CountOverAmps({500, 1}) <<
            CountOverAmps({160, 1}) << CountOverAmps({12, 1}) << CountOverAmps({0, 1}) << CountOverAmps({0, 1}) << CountOverAmps({0, 1}) <<
            CountOverAmps({0, 1}) << CountOverAmps({230, 1}) << CountOverAmps({0, 1}) << CountOverAmps({0, 1}) << CountOverAmps({0, 1}) <<
            CountOverAmps({0, 1}) << CountOverAmps({0, 1}) << CountOverAmps({0, 1}) << CountOverAmps({0, 1}) << CountOverAmps({0, 1});
    logic->calc(Nimp, 2.5, 4.5);
    CATEGORY category = logic->getCategory();
    float koefZap = logic->getKoefZap();
    cmdChart->update(logic);
    widgetMain->setKoefZapCategory(koefZap, getCategoryString(category));
}

WidgetMain* initWidgetMain(MainWindow& window, WidgetChart* widgetChart, CmdChart* const cmdChart) {
    MathLogic* logic = new MathLogic();
    WidgetMain* widgetMain = new WidgetMain();

    widgetMain->setWidget(widgetChart);

    QObject::connect(widgetMain, &WidgetMain::executeAPI, widgetMain, [=, &window](float Lsh, float h, int period, QString path) {
        try {
            QVector<CountOverAmps> Nimp = RawFile::handleFile(path, period);
            logic->calc(Nimp, Lsh, h);

            float koefZap = logic->getKoefZap();
            CATEGORY category = logic->getCategory();
            QString categoryString = getCategoryString(category);
            widgetMain->setKoefZapCategory(koefZap, categoryString);

            cmdChart->update(logic);

        } catch (const ErrorFile& error) {
            widgetMain->errorFile();
            window.viewError(error.what());
        } catch (const ErrorPeriod& error) {
            widgetMain->errorPeriod();
            window.viewError(error.what());
        }
    });

    test(logic, cmdChart, widgetMain);

    return widgetMain;
}

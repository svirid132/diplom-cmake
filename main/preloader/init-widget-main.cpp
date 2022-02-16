#include "init-widget-main.h"
#include "shared-func.h"
#include <QList>
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

QList<QPair<QString, QString>> getTag_texts(MathLogic *const mathLogic, const DataWgtXML& dataWgtXML) {
    QList<QPair<QString, QString>> tag_texts;
    tag_texts << qMakePair("Date", dataWgtXML.date.toString("yyyy-MM-dd"))
              << qMakePair("Rudnik", dataWgtXML.rudnik);
    for (const CountOverAmps& value: mathLogic->getNimp()) {
        tag_texts << qMakePair("N", QString::number(value.countAmps));
    }
    tag_texts << qMakePair("X1", QString::number(mathLogic->getX1()))
              << qMakePair("Lsh", QString::number(mathLogic->getLsh()))
              << qMakePair("Date", dataWgtXML.date.toString("yyyy-MM-dd"))
              << qMakePair("Date", dataWgtXML.date.toString("yyyy-MM-dd"))
              << qMakePair("Date", dataWgtXML.date.toString("yyyy-MM-dd"))
              << qMakePair("Date", dataWgtXML.date.toString("yyyy-MM-dd"))
              << qMakePair("Date", dataWgtXML.date.toString("yyyy-MM-dd"))

}

WidgetMain* initWidgetMain(MainWindow& window, WidgetXML* widgetXML, WidgetChart* widgetChart, CmdChart* const cmdChart) {
    MathLogic* logic = new MathLogic();
    WidgetMain* widgetMain = new WidgetMain();

//    widgetMain->setWidget(widgetChart);
    widgetMain->setWidget(widgetXML, widgetChart);

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

    QObject::connect(widgetXML, &WidgetXML::clickedSave, widgetXML, [=, &window]() {
        try {
            widgetXML->getData();

        } catch (const ErrorFile& error) {
            window.viewError(error.what());
        } catch (const ErrorPeriod& error) {
            window.viewError(error.what());
        }
    });

    test(logic, cmdChart, widgetMain);

    return widgetMain;
}

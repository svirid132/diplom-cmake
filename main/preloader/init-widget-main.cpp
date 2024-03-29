#include "init-widget-main.h"
#include "shared-func.h"
#include <QList>
#include <QListWidget>
#include <QStringListModel>
#include <QTreeView>
#include <cmdchart.h>
#include <math-logic.h>
#include <rawfile.h>
#include <xmlfile.h>
#include <UI/widgetmain.h>
#include <model/n-model.h>

void test(MathLogic *const logic, CmdChart *const cmdChart, WidgetMain *const widgetMain, NModel* const model) {
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

    QStringList list;
    for (auto&& value : Nimp) {
        list << QString::number(value.countAmps);
    }
    model->setStringList(list);

}

QList<QPair<QString, QString>> getTag_texts(MathLogic *const mathLogic, const DataWgtXML& dataWgtXML) {
    QList<QPair<QString, QString>> tag_texts;
    tag_texts << qMakePair(QString("Date"), dataWgtXML.date.toString("yyyy-MM-dd"))
              << qMakePair(QString("Rudnik"), dataWgtXML.rudnik);
    for (auto&& value: mathLogic->getNimp()) {
        tag_texts << qMakePair(QString("N"), QString::number(value.countAmps));
    }
    tag_texts << qMakePair(QString("X1"), QString::number(mathLogic->getX1()))
              << qMakePair(QString("Lsh"), QString::number(mathLogic->getLsh()))
              << qMakePair(QString("h"), QString::number(mathLogic->geth()))
              << qMakePair(QString("N0"), QString::number(mathLogic->getN0()))
              << qMakePair(QString("Nmax"), QString::number(mathLogic->getNmax()))
              << qMakePair(QString("Nzam"), QString::number(mathLogic->getNimp().size()))
              << qMakePair(QString("Nmax_N0"), QString::number(mathLogic->getNmax_N0()))
              << qMakePair(QString("X1_h"), QString::number(mathLogic->getX1_h()))
              << qMakePair(QString("KoefZap"), QString::number(mathLogic->getKoefZap()))
              << qMakePair(QString("Kategor"), getCategoryString(mathLogic->getCategory()))
              << qMakePair(QString("GrZam"), QString("&lt;ExcelChart&gt;\\\\Ggp\\ggp\\GGU\\Департамент горного производства\\ЦГБ\\Сергунин\\ШаблоныФорм\\ГотовыйАКТ\\ГрафикПрогноз.xlsx/Лист1/2/Excel"))
              << qMakePair(QString("GrProgn"), QString("&lt;ExcelChart&gt;\\\\Ggp\\ggp\\GGU\\Департамент горного производства\\ЦГБ\\Сергунин\\ШаблоныФорм\\ГотовыйАКТ\\ГрафикПрогноз.xlsx/Лист1/1/Excel"))
              << qMakePair(QString("XX"), QString::number(dataWgtXML.XX))
              << qMakePair(QString("YY"), QString::number(dataWgtXML.YY))
              << qMakePair(QString("ZZ"), QString::number(dataWgtXML.ZZ))
              << qMakePair(QString("NameVirab"), dataWgtXML.nameVirab)
              << qMakePair(QString("Shablon"), QString("ГрафикПрогноз.xlsx/ПрогнозАКТ.docx"))
              << qMakePair(QString("IzmVip"), dataWgtXML.izmVip);
    return tag_texts;
}

QWidget* initWidgetJoinXml(WidgetXML* const widgetXML, NModel* const model) {

    QWidget* widget = new QWidget();
    QTreeView* listView = new QTreeView();
    QStringList list = QStringList({"fosdjfposd", "fsopdfkdspokf"});
    model->setStringList(list);
    listView->setModel(model);
    listView->setRootIsDecorated(false);
    QHBoxLayout* hLayout = new QHBoxLayout;
    hLayout->addWidget(widgetXML);
    hLayout->addWidget(listView);
    widget->setLayout(hLayout);

    return widget;
}

WidgetMain* initWidgetMain(MainWindow& window, WidgetXML* widgetXML, WidgetChart* widgetChart, CmdChart* const cmdChart) {
    MathLogic* logic = new MathLogic();
    WidgetMain* widgetMain = new WidgetMain();
    widgetMain->setWidget(widgetChart);

    NModel* listModel = new NModel();
    QWidget* widgetnJoinXML = initWidgetJoinXml(widgetXML, listModel);

    QObject::connect(widgetMain, &WidgetMain::executeAPI, widgetMain, [=, &window](float Lsh, float h, int period, QString path) {
        try {
            QVector<CountOverAmps> Nimp = RawFile::handleFile(path, period);
            logic->calc(Nimp, Lsh, h);

            float koefZap = logic->getKoefZap();
            CATEGORY category = logic->getCategory();
            QString categoryString = getCategoryString(category);
            widgetMain->setKoefZapCategory(koefZap, categoryString);

            cmdChart->update(logic);
            widgetMain->setEnabledXMLbtn(true);

            QStringList list;
            for (auto&& value : Nimp) {
                list << QString::number(value.countAmps);
            }
            listModel->setStringList(list);

        } catch (const ErrorFile& error) {
            widgetMain->setEnabledXMLbtn(false);
            widgetMain->errorFile();
            window.viewError(error.what());
        } catch (const ErrorPeriod& error) {
            widgetMain->setEnabledXMLbtn(false);
            widgetMain->errorPeriod();
            window.viewError(error.what());
        }
    });

    QObject::connect(widgetXML, &WidgetXML::clickedSave, widgetXML, [=, &window]() {
        try {
            DataWgtXML dataWgtXML = widgetXML->getData();
            auto tag_texts = getTag_texts(logic, dataWgtXML);
            XMLFile::write("123.xml", tag_texts);
            window.viewSuccess("Файл успешно сохранен");
        } catch (const ErrorFile& error) {
            window.viewError(error.what());
        } catch (const ErrorPeriod& error) {
            window.viewError(error.what());
        }
    });

    QObject::connect(widgetMain, &WidgetMain::clickedSaveXML, widgetMain, [=](bool flag) {
        if (flag) {
            widgetMain->setEnabledPanel(!flag);
            widgetMain->setWidget(widgetnJoinXML);
        } else {
            widgetMain->setEnabledPanel(!flag);
            widgetMain->setWidget(widgetChart);
        }
    });

    test(logic, cmdChart, widgetMain, listModel);


    return widgetMain;
}

#include "init-widget-main.h"
#include "../shared-func/shared-func.h"
#include <QList>
#include <QListWidget>
#include <QStringListModel>
#include <QTreeView>
#include <../cmdchart.h>
#include <docx/docx.h>
#include <math-logic.h>
#include <rawfile.h>
#include <xmlfile.h>
#include <QtCore/QDir>
#include "../UI/widgetmain.h"
#include "../model/n-model.h"

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
    qDebug() << "point:" <<logic->getCriticalPoint();
    QStringList list;
    for (auto&& value : Nimp) {
        list << QString::number(value.countAmps);
    }
    model->setStringList(list);

    widgetMain->setModeCalc(MODE_CALC::XML);

}

//For xml
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
    widgetMain->setModeCalc(MODE_CALC::RAW);

    NModel* listModel = new NModel();
    QWidget* widgetnJoinXML = initWidgetJoinXml(widgetXML, listModel);
//    widgetnJoinXML->setParent(widgetMain);
//    widgetnJoinXML->hide();

    QObject::connect(widgetMain, &WidgetMain::executeAPI, widgetMain, [=, &window](float Lsh, float h, int period, QString path) {
        try {
            QVector<CountOverAmps> Nimp;
            switch (widgetMain->modelCalc()) {
                case MODE_CALC::RAW:
                   Nimp = RawFile::handleFile(path, period);
                    logic->calc(Nimp, Lsh, h);
                    break;
                case MODE_CALC::XML:
                    Nimp = logic->getNimp();
                    logic->calc(Lsh, h);
                    break;
            }

            float koefZap = logic->getKoefZap();
            CATEGORY category = logic->getCategory();
            QString categoryString = getCategoryString(category);
            widgetMain->setKoefZapCategory(koefZap, categoryString);

            cmdChart->update(logic);
            widgetMain->successChange();

            QStringList list;
            for (auto&& value : Nimp) {
                list << QString::number(value.countAmps);
            }
            listModel->setStringList(list);

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
            DataWgtXML dataWgtXML = widgetXML->getData();
            auto tag_texts = getTag_texts(logic, dataWgtXML);

//            Скалистый_2021-10-08_РВ-1_2021-11-06T13_06_13;
            QString date = dataWgtXML.date.toString("yyyy-MM-dd");
            QString currentDate = QDateTime::currentDateTime().toString("yyyy-MM-ddThh_mm_ss");
            QString filename = QString("%1_%2_%3_%4.xml").arg(dataWgtXML.rudnik).arg(date).arg(dataWgtXML.nameVirab).arg(currentDate);

            XMLFile::write("files/" + filename, tag_texts);
            window.viewSuccess("Файл успешно сохранен");
        } catch (const ErrorFile& error) {
            window.viewError(error.what());
        } catch (const ErrorPeriod& error) {
            window.viewError(error.what());
        }
    });

    QObject::connect(widgetMain, &WidgetMain::clickedSaveXML, widgetMain, [=](bool flag) {
        if (flag) {
            widgetMain->setEnabledPanel(false);
            widgetMain->setWidget(widgetnJoinXML);
        } else {
            widgetMain->setEnabledPanel(true);
            widgetMain->setWidget(widgetChart);
        }
    });

    QObject::connect(widgetMain, &WidgetMain::fromXml, widgetMain, [=, &window]() {
        QString filepath = widgetMain->openFileXml();
        if (filepath != "") {
            bool ok;
            XmlData xmlData = XMLFile::read(filepath, ok);
            if (ok) {
                QVector<CountOverAmps> Nimp;
                for (int val: xmlData.imps) {
                    Nimp.append(CountOverAmps({val, -1}));
                }
                logic->calc(Nimp, xmlData.Lsh, xmlData.h);
                logic->setNimp(Nimp);

                float koefZap = logic->getKoefZap();
                CATEGORY category = logic->getCategory();
                QString categoryString = getCategoryString(category);
                widgetMain->setKoefZapCategory(koefZap, categoryString);

                cmdChart->update(logic);
                widgetMain->successChange();

                QStringList list;
                for (auto&& value : Nimp) {
                    list << QString::number(value.countAmps);
                }
                listModel->setStringList(list);

                widgetMain->setModeCalc(MODE_CALC::XML);

                window.viewSuccess("Файл успешно прочитан!");
            } else {
                window.viewError("Файл не прочитан!");
            }
        }
    });

    QObject::connect(widgetXML, &WidgetXML::createDocx, widgetXML, [=, &window]() {

        Docx docx;
        DocData docData;
        docData.N0 = logic->getN0();
        docData.Nmax = logic->getNmax();
        docData.Nmax_N0 = logic->getNmax_N0();
        DataWgtXML dataWgtXML = widgetXML->getData();
        docData.X = dataWgtXML.XX;
        docData.Xm = logic->getX1();
        docData.Xm_h= logic->getX1_h();
        docData.Y = dataWgtXML.YY;
        docData.Z = dataWgtXML.ZZ;
        docData.rudnik = dataWgtXML.rudnik;
        docData.product = dataWgtXML.nameVirab;
        docData.dateProduct = dataWgtXML.date.toString("dd.MM.yyyy");
        docData.year = QString::number(dataWgtXML.date.year());
        docData.category = getCategoryString(logic->getCategory());
        docData.h = logic->geth();
        docData.koefZap = smath::roundFloat(logic->getKoefZap());
        if (window.isDataCommission()) {
            DataCommission data = window.getDataCommission();
            docData.docCommission.nameWritter = data.nameWritter;
            docData.docCommission.posDescWritter = data.posDescWritter;
            docData.docCommission.nameMain = data.nameMain;
            docData.docCommission.posDescMain = data.posDescMain;
            docData.docCommission.nameMembOne = data.nameMembOne;
            docData.docCommission.posDescMembOne = data.posDescMembOne;
            docData.docCommission.nameMembTwo = data.nameMembTwo;
            docData.docCommission.posDescMembTwo = data.posDescMembTwo;
        } else {
            widgetXML->errorCommission();
            return;
        }

        docx.setData(docData, logic->getGlub_Nimp().toList(), logic->getCriticalPoint());

        QString filename = Docx::createFileName(docData.product, docData.dateProduct);
        QString filepath = "files/" + filename;
        if ( isFileExists(filepath) ) {
            QString problem = QString("Фйла с именем \"%1\" уже создан.").arg(filename);
            QString question = "Перезаписать файл?";
            bool isAccept = window.dialogQuestion(problem, question);
            if (!isAccept) return;
        }

        try {
            docx.create(filepath);
            window.viewSuccess("Файл успешно сохранен");
        } catch (const ErrorFile& error) {
            window.viewError(error.what());
        }
    });

    QObject::connect(widgetXML, &WidgetXML::clickedCommission, [=, &window](){
        window.dialogCommission();
    });

    QObject::connect(widgetXML, &WidgetXML::clickedXmlToDocx, [=, &window](){
        if (window.isDataCommission()) {
            window.dialogConveter();
        } else {
            widgetXML->errorCommission();
        }
    });

    test(logic, cmdChart, widgetMain, listModel);

    //debug
//    widgetMain->setEnabledPanel(false);
//    widgetMain->setWidget(widgetnJoinXML);

    return widgetMain;
}

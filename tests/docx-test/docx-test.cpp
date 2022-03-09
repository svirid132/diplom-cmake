#include <QtTest>
#include <QCoreApplication>
#include <QDebug>
#include <QVector>
#include <docx-data.h>
#include <handler-chart.h>
#include "handler-document.h"
#include "smath.h"

//int *const ptr - константные указатели
//const int *ptr - константные значения

class DocxTest : public QObject
{
    Q_OBJECT

public:

private:
    DocData docData;

private slots:
    void initTestCase();
    void handleDocument();
    void handleChart1();
    void handleChart2();
};

void DocxTest::initTestCase()
{
    docData.N0 = 20;
    docData.Nmax = 1999;
    docData.Nmax_N0 = smath::roundFloat(float(docData.Nmax) / float(docData.N0));//99.95
    docData.Xm = 123.3;
    docData.h = 4.5;
    docData.Xm_h = smath::roundFloat(float(docData.Xm) / float(docData.h));//27.4
    docData.category = "НЕОПАСНО";
    docData.X = 21;
    docData.Y = 22;
    docData.Z = -23.23;

    //test document handler
    HandlerDocument handDoc;
    QFile rawFile(":/assets/document-0.xml");
    rawFile.open(QIODevice::ReadOnly);
    QString rawData = QString::fromUtf8(rawFile.readAll());
    handDoc.setInfo(rawData, docData);
    QString handleDoc = handDoc.handleDocument();
    QFile fileWrite("D:\\Project\\diplom\\diplom-cmake\\tests\\docx-test\\assets\\document-0-handler.xml");
    qDebug() << "fileWrite: " << fileWrite.open(QIODevice::WriteOnly);
    fileWrite.write(handleDoc.toUtf8());
    fileWrite.close();
}

void DocxTest::handleDocument(){
    QFile rawFile(":/assets/document-0.xml");
    rawFile.open(QIODevice::ReadOnly);
    QString rawData = QString::fromUtf8(rawFile.readAll());

    QFile file(":/assets/document-right-2.xml");
    file.open(QIODevice::ReadOnly);
    QString data = QString::fromUtf8(file.readAll());

    HandlerDocument handlerDoc;
    handlerDoc.setInfo(rawData, docData);
    QString handleData = handlerDoc.handleDocument();

    //Для теста теста
//    QFile fileWrite("document.xml");
//    fileWrite.open(QIODevice::WriteOnly);
//    fileWrite.write(handleData.toUtf8());

    //Сравнение двух файлов строк, вывод несовпадений
    const int len = 10;
    const int start = 0;
    for (int i = start; i < handleData.count(); i+=len) {
        QString strData = data.mid(i, len);
        QString strHandle = handleData.mid(i, len);
        if (strData != strHandle){
            qDebug() << "pos:" << i;
            qDebug() << "data:" << data.mid(i, len) << Qt::endl;
            qDebug() << "handle-data:" << handleData.mid(i, len) << Qt::endl;
            break;
        }
    }

    QVERIFY(handleData == data);
}

void DocxTest::handleChart1() {

    QList<QPointF> pointChart1;
    pointChart1.append({0, 223});
    pointChart1.append({0.267, 394});
    HandlerChart handChart;
    QFile fileRaw(":/assets/chart1-0.xml");
    qDebug() << fileRaw.open(QIODevice::ReadOnly);
    QString rawData = QString::fromUtf8(fileRaw.readAll());
    handChart.setRawData(rawData);
    handChart.appendChart(pointChart1, CHART_NUMBER::first);
    QString handleData = handChart.handleCharts();

    QFile fileData(":/assets/chart1-1.xml");
    qDebug() << fileData.open(QIODevice::ReadOnly);
    QString data = QString::fromUtf8(fileData.readAll());

    //Сравнение двух файлов строк, вывод несовпадений
    const int len = 10;
    const int start = 0;
    for (int i = start; i < handleData.count(); i+=len) {
        QString strData = data.mid(i, len);
        QString strHandle = handleData.mid(i, len);
        if (strData != strHandle){
            qDebug() << "pos:" << i;
            qDebug() << "data:" << data.mid(i, len) << Qt::endl;
            qDebug() << "handle-data:" << handleData.mid(i, len) << Qt::endl;
            break;
        }
    }

    QVERIFY(data == handleData);
}

void DocxTest::handleChart2() {

    QList<QPointF> pointChart2;
    pointChart2.append({4.776, 4.098});
    HandlerChart handChart;
    QFile fileRaw(":/assets/chart2-0.xml");
    qDebug() << fileRaw.open(QIODevice::ReadOnly);
    QString rawData = QString::fromUtf8(fileRaw.readAll());
    handChart.setRawData(rawData);
    handChart.appendChart(pointChart2, CHART_NUMBER::second, "НЕОПАСНО");
    QString handleData = handChart.handleCharts();

    QFile fileData(":/assets/chart2-1.xml");
    qDebug() << fileData.open(QIODevice::ReadOnly);
    QString data = QString::fromUtf8(fileData.readAll());

    //Сравнение двух файлов строк, вывод несовпадений
    const int len = 50;
    const int start = 0;
    for (int i = start; i < handleData.count(); i+=len) {
        QString strData = data.mid(i, len);
        QString strHandle = handleData.mid(i, len);
        if (strData != strHandle){
            qDebug() << "pos:" << i;
            qDebug() << "data:" << data.mid(i, len) << Qt::endl;
            qDebug() << "handle-data:" << handleData.mid(i, len) << Qt::endl;
            break;
        }
    }

    QVERIFY(data == handleData);
}

QTEST_APPLESS_MAIN(DocxTest)//без GUI
#include "docx-test.moc"

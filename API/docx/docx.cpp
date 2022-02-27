#include "docx.h"
#include "handler-chart.h"
#include "handler-document.h"

#include <QDebug>
#include <QTemporaryFile>
#include "libary/zip/zip.h"
#include <quazip/quazip.h>
#include <quazip/quazipfile.h>

Docx::Docx()
{

}

QPointF handleCriticalPoint(const QPointF& point) {
    float handX = point.x() * 20 + 1;//из Exel
    QPointF handP = {handX, point.y()};
    return handP;
}

void Docx::setData(const DocData &docData, const QList<QPointF> &chartGlub_Nimp, QPointF criticalPoint)
{
    this->docData = docData;
    this->chartGlub_Nimp = chartGlub_Nimp;
    this->criticalPoint = handleCriticalPoint(criticalPoint);
}

void Docx::create()
{
    QString zipName = ":/assets/docx-1.docx";
    QuaZip zip(zipName);
    if (!zip.open(QuaZip::mdUnzip)) {
        qWarning("Couldn't open %s", zipName.toUtf8().constData());
    }
    QuaZipFile inFile(&zip);
    QList<QPair<QString, QByteArray>> files;
    for(bool more=zip.goToFirstFile(); more; more=zip.goToNextFile()) {
        QuaZipFileInfo info;
        zip.getCurrentFileInfo(&info);
        QString filename = zip.getCurrentFileName();
        if(!inFile.open(QIODevice::ReadOnly)) {
            qDebug() << "not open inFile:" << filename;
        }
        QByteArray data = inFile.readAll();
        if (filename == "word/document.xml") {
            HandlerDocument handDoc;
            QString rawStr = QString::fromUtf8(data);
            handDoc.setInfo(rawStr, docData);
            QString str = handDoc.handleDocument();
            data = str.toUtf8();
        } else if (filename == "word/charts/chart1.xml") {
            HandlerChart handChart;
            QString rawStr = QString::fromUtf8(data);
            handChart.setRawData(rawStr);
            handChart.appendChart(chartGlub_Nimp, CHART_NUMBER::first);
            QString str = handChart.handleCharts();
            data = str.toUtf8();
        } else if (filename == "word/charts/chart2.xml") {
            HandlerChart handChart;
            QString rawStr = QString::fromUtf8(data);
            handChart.setRawData(rawStr);
            handChart.appendChart({criticalPoint}, CHART_NUMBER::second, docData.category);
            QString str = handChart.handleCharts();
            data = str.toUtf8();
        }
        files.append({filename, data});
        inFile.close();
    }
    zip.close();

    QuaZip zipDocx("create-docx.docx");
    qDebug() << "create-docx";
    if (!zipDocx.open(QuaZip::mdCreate)) qDebug() << "zipDocx:" << "false";
    QuaZipFile outFile(&zipDocx);
    for(auto& file: files){
        if (outFile.open(QIODevice::WriteOnly, QuaZipNewInfo(file.first))) {
            qDebug() << "file write:" << file.first;
            outFile.write(file.second);
            outFile.close();
        } else {
            qDebug() << "not file:" << file.first;
        }
    }
    zipDocx.close();

    if(zip.getZipError() == UNZ_OK) {
      qDebug() << "error not!";
    }
}

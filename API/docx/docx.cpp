#include "docx.h"
#include "handler-chart.h"
#include "handler-document.h"

#include <QDebug>
#include <QTemporaryFile>
#include "libary/zip/zip.h"
#include <quazip/quazip.h>
#include <quazip/quazipfile.h>
#include "error.h"

Docx::Docx() {

}

QPointF handleCriticalPoint(const QPointF &point) {
    float handX = point.x() * 20 + 1;//из Excel
    QPointF handP = {handX, point.y()};
    return handP;
}

void Docx::setData(const DocData &docData, const QList<QPointF> &chartGlub_Nimp, QPointF criticalPoint) {
    this->docData = docData;
    this->chartGlub_Nimp = chartGlub_Nimp;
    this->criticalPoint = handleCriticalPoint(criticalPoint);
}

bool Docx::saveDocx(QString filePath, const QList<QPair<QString, QByteArray>> &files) {
    QuaZip zipDocx(filePath);
    if (!zipDocx.open(QuaZip::mdCreate)) {
        return false;
    };
    QuaZipFile outFile(&zipDocx);
//    qDebug() << zipDocx.getZipName(); path
    for (auto &file: files) {
        if (outFile.open(QIODevice::WriteOnly, QuaZipNewInfo(file.first))) {
            outFile.write(file.second);
            outFile.close();
        } else {
            return false;
        }
    }
    zipDocx.close();
    return true;
}

void Docx::handleFiles(QList<QPair<QString, QByteArray>> &files) {
    for (auto &file: files) {
        if (file.first == "word/document.xml") {
            HandlerDocument handDoc;
            QString rawStr = QString::fromUtf8(file.second);
            handDoc.setInfo(rawStr, docData);
            QString handStr = handDoc.handleDocument();
            file.second = handStr.toUtf8();
        } else if (file.first == "word/charts/chart1.xml") {
            HandlerChart handChart;
            QString rawStr = QString::fromUtf8(file.second);
            handChart.setRawData(rawStr);
            handChart.appendChart(chartGlub_Nimp, CHART_NUMBER::first);
            QString handStr = handChart.handleCharts();
            file.second = handStr.toUtf8();
        } else if (file.first == "word/charts/chart2.xml") {
            HandlerChart handChart;
            QString rawStr = QString::fromUtf8(file.second);
            handChart.setRawData(rawStr);
            handChart.appendChart({criticalPoint}, CHART_NUMBER::second, docData.category);
            QString str = handChart.handleCharts();
            file.second = str.toUtf8();
        }
    }
}

QList<QPair<QString, QByteArray>> Docx::externTemplate() {
    QString zipName = ":/template.docx";
    QuaZip zip(zipName);
    QList<QPair<QString, QByteArray>> files;
    if (!zip.open(QuaZip::mdUnzip)) {
        throw ErrorFile::template_();
        //qWarning("Couldn't open %s", zipName.toUtf8().constData());
    }
    QuaZipFile inFile(&zip);
    for (bool more = zip.goToFirstFile(); more; more = zip.goToNextFile()) {
        QuaZipFileInfo info;
        zip.getCurrentFileInfo(&info);
        QString filename = zip.getCurrentFileName();
        if (!inFile.open(QIODevice::ReadOnly)) {
            throw ErrorFile::template_();
//            qDebug() << "not open inFile:" << filename;
        }
        QByteArray data = inFile.readAll();
        files.append({filename, data});
        inFile.close();
    }
    zip.close();

    if (zip.getZipError() != UNZ_OK) {
        throw ErrorFile::template_();
    }

    return files;
}

void Docx::create(QString pathFile) {

    QList<QPair<QString, QByteArray>> files = externTemplate();
    handleFiles(files);
    if (!saveDocx(pathFile, files)) {
        throw ErrorFile::save();
    }

}

QString Docx::createFileName(const QString& product, const QString& dateProduct ) {
    QString filename = QString("АКТ %1 от %2.docx").arg(product).arg(dateProduct);
    return filename;
}

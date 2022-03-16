//
// Created by Пользователь on 14.03.2022.
//

#include "XMLtoDOCX.h"
#include "../math-logic/math-logic.h"
#include <QtCore/QXmlStreamReader>
#include <QtCore/QFile>
#include <QDebug>
#include <QDate>
#include <docx.h>

XMLtoDOCX::XMLtoDOCX()
{

}

void XMLtoDOCX::setFilePathXML(const QString &path) {
    xmlFilePath = path;
}

void XMLtoDOCX::setPathDocx(const QString &path) {
    docxPath = path;
}

void XMLtoDOCX::saveDocx() {
    Docx doc;
    doc.setData(
            paramDocx.docData,
            paramDocx.Glub_Nimp,
            paramDocx.criticalPoint
    );
    QString filePath = getDocxFilePath();
    doc.create(filePath);
}

QString XMLtoDOCX::getDocxFilePath() {
    QString filePath = Docx::createFileName(paramDocx.docData.product, paramDocx.docData.dateProduct);
    return docxPath + "/" + filePath;
}

bool XMLtoDOCX::convert(const DocCommission &docCommission) {

    QFile xmlFile(xmlFilePath);
    if (!xmlFile.open(QIODevice::ReadOnly)) {
        return false;
    }

    DocData docData;

    QXmlStreamReader xml;
    xml.setDevice(&xmlFile);
    QList<int> imps;
    float Lsh;
    while(!xml.atEnd()) {
        xml.readNext();
        if (xml.isStartElement()) {
            QString tag = xml.name().toString();
            xml.readNext();
            QString text = xml.text().toString();
            if (tag == "Date") {
                QDate date = QDate::fromString(text, "yyyy-MM-dd");
                docData.dateProduct = date.toString("dd.MM.yyyy");
                docData.year = date.toString("yyyy");
            } else if(tag == "Rudnik") {
                docData.rudnik = text;
            } else if (tag == "N") {
                imps.append(QString(text).toInt());
            } else if(tag == "X1") {
                docData.Xm = QString(text).toFloat();
            } else if (tag == "Lsh") {
                Lsh = QString(text).toFloat();
            } else if (tag == "h") {
                docData.h = QString(text).toFloat();
            } else if (tag == "N0") {
                docData.N0 = QString(text).toInt();
            } else if (tag == "Nmax") {
                docData.Nmax = QString(text).toInt();
            } else if (tag == "Nzam") {

            } else if (tag == "Nmax_N0") {
                docData.Nmax_N0 = QString(text).toFloat();
            } else if (tag == "X1_h") {
                docData.Xm_h = QString(text).toFloat();
            } else if (tag == "koefZap") {
                docData.koefZap = QString(text).toFloat();
            } else if(tag == "Kategor") {
                docData.category = text;
            } else if (tag == "XX") {
                docData.X = QString(text).toFloat();
            } else if(tag == "YY") {
                docData.Y = QString(text).toFloat();
            } else if(tag == "ZZ") {
                docData.Z = QString(text).toFloat();
            } else if (tag == "NameVirab") {
                docData.product = QString(text);
            }
        }
    }
    docData.docCommission = docCommission;

    //Только ради Nimp_Glub
    MathLogic logic;
    QVector<CountOverAmps> overImps;
    for (int imp : imps) {
        CountOverAmps overImp;
        overImp.countAmps = imp;
        overImps.append(overImp);
    }
    logic.calc(overImps, Lsh, docData.h);

    paramDocx.docData = docData;
    paramDocx.Glub_Nimp = logic.getGlub_Nimp().toList();
    paramDocx.criticalPoint = { docData.Xm_h, docData.Nmax_N0 };

    return true;
}

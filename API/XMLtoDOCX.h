//
// Created by Пользователь on 14.03.2022.
//

#ifndef DIPLOM_CMAKE_XMLTODOCX_H
#define DIPLOM_CMAKE_XMLTODOCX_H


#include <QtCore/QString>
#include <functional>
#include "docx/docx-data.h"
#include <QPointF>
#include <QList>

//TODO
class XMLtoDOCX {
public:
    XMLtoDOCX();

    void setFilePathXML(const QString& path);
    void setPathDocx(const QString& path);
    bool convert(const DocCommission& docCommission);
    void saveDocx();
    QString getDocxFilePath();

private:
    QString xmlFilePath;
    QString docxPath;

    struct ParamDocx {
        DocData docData;
        QList<QPointF> Glub_Nimp;
        QPointF criticalPoint;
    } paramDocx;
};


#endif //DIPLOM_CMAKE_XMLTODOCX_H

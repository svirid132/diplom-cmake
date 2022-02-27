#ifndef HANDLERDOCUMENT_H
#define HANDLERDOCUMENT_H

#include <QList>
#include <QString>
#include <QXmlStreamReader>
#include "docx-data.h"

class HandlerDocument {
public:
    HandlerDocument();
    void setInfo(const QString& rawData, DocData docData);
    QString handleDocument();

private:
    QString rawData;
    DocData docData;
    struct SpecSymbol {
        QString X = "`{X}`";
        QString Y = "`{Y}`";
        QString Z = "`{Z}`";
        QString Xm = "`{Xm}`";
        QString N0 = "`{N0}`";
        QString Nmax = "`{Nmax}`";
        QString Nmax_N0 = "`{Nmax/N0}`";
        QString h = "`{h}`";
        QString Xm_h = "`{Xm/h}`";
        QString category = "`{category}`";
    } specSymbol;

    QString handleMathRaplace(const QString& specSymbol);
    QString handler(QXmlStreamReader& xml);
    QList<QPair<StartEnd, QString>> handleElements(QXmlStreamReader& xml);
    QList<QPair<StartEnd, QString> > handleText(QXmlStreamReader &xml);
};

#endif // HANDLERDOCUMENT_H

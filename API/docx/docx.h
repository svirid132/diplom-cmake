#ifndef DOCX_H
#define DOCX_H

#include "docx-data.h"

#include <QList>
#include <QPointF>



class Docx
{
public:
    Docx();
    void setData(const DocData& docData, const QList<QPointF>& chartGlub_Nimp, QPointF criticalPoint);
    void create(QString pathFile);//create и save

private:
    DocData docData;
    QList<QPointF> chartGlub_Nimp;
    QPointF criticalPoint;
    void saveDocx(QString filePath, const QList<QPair<QString, QByteArray>>& files);

    void handleFiles(QList<QPair<QString, QByteArray>> &files);

    QList<QPair<QString, QByteArray>> externTemplate();
};

#endif // DOCX_H

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
    void create();//create и save

private:
    DocData docData;
    QList<QPointF> chartGlub_Nimp;
    QPointF criticalPoint;
};

#endif // DOCX_H

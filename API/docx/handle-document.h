#ifndef HANDLERDOCUMENT_H
#define HANDLERDOCUMENT_H

#include <QString>
#include "docx-data.h"

QString handleDocument(const QString& rawData);

class HandlerDocument {
public:
    HandlerDocument(const QString& rawData, DocData docData);

};

#endif // HANDLERDOCUMENT_H

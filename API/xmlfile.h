#ifndef XMLFILE_H
#define XMLFILE_H

#include <QPair>
#include <QString>
#include "API-var.h"

class XMLFile
{
public:
    static void write(QString path, const QList<QPair<QString, QString>>& tag_texts);
    static XmlData read(const QString& path, bool& ok);

private:
    XMLFile();
};

#endif // XMLFILE_H

#ifndef XMLFILE_H
#define XMLFILE_H

#include <QPair>
#include <QString>

class XMLFile
{
public:
    static void write(QString path, const QList<QPair<QString, QString>>& tag_texts);
private:
    XMLFile();
};

#endif // XMLFILE_H

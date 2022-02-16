#include "xmlfile.h"

#include <QDebug>
#include <QFile>
#include <QXmlStreamWriter>

void XMLFile::write(QString path, const QList<QPair<QString, QString>>& tag_texts)
{
    QFile file(path);
    qDebug() << "open file:" << file.open(QIODevice::WriteOnly);
    QXmlStreamWriter writer;
    writer.setAutoFormatting(true);
    writer.setDevice(&file);
    writer.writeStartDocument();
    const QString defaultTag = "<?mso-infoPathSolution productVersion=\"15.0.0\" PIVersion=\"1.0.0.0\" href=\"file:///\\\\Ggp\\ggp\\GGU\\Департамент%20горного%20производства\\ЦГБ\\Сергунин\\ШаблоныФорм\\Прогноз.xsn\" name=\"urn:schemas-microsoft-com:office:infopath:O0ncmng:-myXSD-2020-05-01T04-37-59\" solutionVersion=\"1.0.0.104\" ?><?mso-application progid=\"InfoPath.Document\" versionProgid=\"InfoPath.Document.3\"?>";
    file.write(defaultTag.toUtf8());

    const QString prefixTag = "my:";

    writer.writeStartElement(prefixTag + "PrognozM");
    writer.writeAttribute("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
    writer.writeAttribute("xmlns:my", "http://schemas.microsoft.com/office/infopath/2003/myXSD/2020-05-01T04:37:59");
    writer.writeAttribute("xmlns:xd", "http://schemas.microsoft.com/office/infopath/2003");
    writer.writeAttribute("xml:lang", "ru");

    for (const QPair<QString, QString>& tag_text: tag_texts){
        writer.writeStartElement(prefixTag + tag_text.first);
        writer.writeCharacters("");
        writer.device()->write(tag_text.second.toUtf8());
        writer.writeEndElement();
    }

    writer.writeEndElement(); // PrognozM
    writer.writeEndDocument();
    file.close();
}

XMLFile::XMLFile()
{

}

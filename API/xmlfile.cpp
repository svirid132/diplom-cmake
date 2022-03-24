#include "xmlfile.h"

#include <QDebug>
#include <QFile>
#include <QXmlStreamWriter>
#include <QtCore/QDate>

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

XmlData XMLFile::read(const QString &path, bool& ok) {

    ok = false;

    QFile xmlFile(path);
    if (!xmlFile.open(QIODevice::ReadOnly)) {
        return XmlData();
    }

    XmlData xmlData;

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
                xmlData.product = date.toString("dd.MM.yyyy");
            } else if(tag == "Rudnik") {
                xmlData.rudnik = text;
            } else if (tag == "N") {
                imps.append(QString(text).toInt());
            } else if(tag == "X1") {
                xmlData.Xm = QString(text).toFloat();
            } else if (tag == "Lsh") {
                Lsh = QString(text).toFloat();
                xmlData.Lsh = Lsh;
            } else if (tag == "h") {
                xmlData.h = QString(text).toFloat();
            } else if (tag == "N0") {
                xmlData.N0 = QString(text).toInt();
            } else if (tag == "Nmax") {
                xmlData.Nmax = QString(text).toInt();
            } else if (tag == "Nzam") {

            } else if (tag == "Nmax_N0") {
            } else if (tag == "X1_h") {
            } else if (tag == "koefZap") {
                xmlData.koefZap = QString(text).toFloat();
            } else if(tag == "Kategor") {
                xmlData.category = text;
            } else if (tag == "XX") {
                xmlData.X = QString(text).toFloat();
            } else if(tag == "YY") {
                xmlData.Y = QString(text).toFloat();
            } else if(tag == "ZZ") {
                xmlData.Z = QString(text).toFloat();
            } else if (tag == "NameVirab") {
                xmlData.product = QString(text);
            } else if (tag == "IzmVip") {
                xmlData.person = QString(text);
            }
        }
    }

    xmlData.imps = imps;
    if(xmlData.N0 != -1) ok = true;


    return xmlData;
}

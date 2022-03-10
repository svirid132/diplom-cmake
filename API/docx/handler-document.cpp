#include "handler-document.h"
#include <QDebug>
#include <QList>
#include <QXmlStreamReader>

HandlerDocument::HandlerDocument() {

}

void HandlerDocument::setInfo(const QString &rawData, DocData docData) {
    this->rawData = rawData;
    this->docData = docData;
}

QString HandlerDocument::handleMathRaplace(const QString &specSymb, DocxFlags::Texts specText) {

    QString text = "";
    if (docData.N0 != -1) {//Не тествовый режим!
        text = specSymb;
        text
            .replace(specSymbol.X, QString::number(docData.X))
            .replace(specSymbol.Y, QString::number(docData.Y))
            .replace(specSymbol.Z, QString::number(docData.Z))
            .replace(specSymbol.Xm, QString::number(docData.Xm))
            .replace(specSymbol.N0, QString::number(docData.N0))
            .replace(specSymbol.Nmax, QString::number(docData.Nmax))
            .replace(specSymbol.Nmax_N0, QString::number(docData.Nmax_N0))
            .replace(specSymbol.h, QString::number(docData.h))
            .replace(specSymbol.Xm_h, QString::number(docData.Xm_h))
            .replace(specSymbol.category, docData.category);
    } else {
        if (specSymb[0] == ' ') text = " ";
        if (specText & DocxFlags::num) {
            text += "1999";
        } else {
            text += "words";
        }
        int lastPos = specSymb.length() - 1;
        if (specSymb[lastPos] == ' ') text += " ";
    }

    //Вставка спец текста
    QString xmlText = "";
    if (specText & DocxFlags::text) {
        xmlText = "<w:r w:rsidR=\"00CD17DF\" w:rsidRPr=\"00CD17DF\"><w:rPr><w:rFonts w:ascii=\"Tahoma\" w:hAnsi=\"Tahoma\" w:cs=\"Tahoma\"/>%2</w:rPr><w:t%1>%3</w:t></w:r>";

        if (specText & DocxFlags::textSpace) {
            xmlText = xmlText.arg(" xml:space=\"preserve\"");
        } else {
            xmlText = xmlText.arg("");
        }

        if (specText & DocxFlags::textBold) {
            xmlText = xmlText.arg("<w:b/>");
        } else {
            xmlText = xmlText.arg("");
        }
    } else if (DocxFlags::num) {
        xmlText = "<m:r><w:rPr><w:rFonts w:ascii=\"Cambria Math\" w:eastAsia=\"Calibri\" w:hAnsi=\"Cambria Math\" w:cs=\"Tahoma\" /><w:lang w:eastAsia=\"en-US\" /></w:rPr><m:t>%1</m:t></m:r>";
    }

    xmlText = xmlText.arg(text);

    return xmlText;
}

QString HandlerDocument::handler(QXmlStreamReader &xml, bool &isSpace, bool &isBold) {
    bool isEnd = false;
    QString text = "";
    while (!(isEnd)) {
        QXmlStreamReader::TokenType tokenType = xml.readNext();
        auto attributes = xml.attributes();
        QString nameTag = xml.name().toString();

        if (tokenType == QXmlStreamReader::StartElement && nameTag == "t") {
            text += xml.readElementText();
        }

        if (!isSpace && attributes.hasAttribute("xml:space")) {
            isSpace = true;
        }

        if (!isBold && nameTag == "b") {
            isBold = true;
        }

        if (tokenType == QXmlStreamReader::EndElement && nameTag == "r") {
            isEnd = true;
        }
    }
    return text;
}

QList<QPair<StartEnd, QString>> HandlerDocument::handleText(QXmlStreamReader &xml) {
    QList<QPair<StartEnd, QString>> replaceTexts;
    bool isEnd = false;
    bool isTextReplace = false;// Для `{Nmax
    QString textReplace = "";//`{Nmax}`
    int startElementDelete = -1;
    int endElementDelete = -1;
    bool isBold = false;
    bool isSpace = false;
    while (!(isEnd)) {
        int startElem = xml.characterOffset();
        QXmlStreamReader::TokenType tokenType = xml.readNext();
        QString prefix = xml.prefix().toString();
        QString nameTag = xml.name().toString();

        if (tokenType == QXmlStreamReader::StartElement && nameTag == "r") {
            QString pathText = handler(xml, isSpace, isBold);

            //начало и конец
            switch (pathText.count('`')) {
                case 2:
                    textReplace = pathText;
                    isTextReplace = false;
                    startElementDelete = startElem;
                    break;
                case 1:
                    isTextReplace = !isTextReplace;
                    if (!isTextReplace) {
                        textReplace += pathText;
                    } else {
                        startElementDelete = startElem;
                    }
                    break;
            };

            //середина
            if (isTextReplace) {
                textReplace += pathText;
            }

            if (textReplace != "" && !isTextReplace) {
                DocxFlags::Texts specText;

                if (prefix == "w") {
                    specText = DocxFlags::Text::text;
                } else if (prefix == "m") {
                    specText = DocxFlags::Text::num;
                }
                if (isBold) specText = specText | DocxFlags::textBold;
                if (isSpace) specText = specText | DocxFlags::textSpace;
                QString handleText = handleMathRaplace(textReplace, specText);
                endElementDelete = xml.characterOffset();
                replaceTexts.append(QPair<StartEnd, QString>{{startElementDelete, endElementDelete}, handleText});
                textReplace = "";
                isBold = false;
                isSpace = false;
            }

        }

        if (tokenType == QXmlStreamReader::EndElement && nameTag == "p") {
            isEnd = true;
        }
    }
    return replaceTexts;
}

QList<QPair<StartEnd, QString>> HandlerDocument::handleElements(QXmlStreamReader &xml) {
    QList<QPair<StartEnd, QString>> replaceTexts;
    QString name = xml.name().toString();
    if (name == "p") {
        auto result = handleText(xml);
        replaceTexts.append(result);
    }

    return replaceTexts;
}

QString HandlerDocument::handleDocument() {
    QXmlStreamReader xml(rawData);
    QList<QPair<StartEnd, QString>> replaceTexts;

    while (!xml.atEnd()) {
        xml.readNext();
        if (xml.isStartElement()) {
            QList<QPair<StartEnd, QString>> replaceTexts_l = handleElements(xml);
            replaceTexts.append(replaceTexts_l);
        }
    }

    if (xml.hasError()) {
        qDebug() << "Ошибка чтения";
    }

    QString data = rawData;
    for (int i = replaceTexts.count() - 1; i > -1; --i) {
        auto el = replaceTexts.at(i);
        QString textReplace = data.mid(el.first.start, el.first.end - el.first.start);
        data.remove(el.first.start, el.first.end - el.first.start);
        data.insert(el.first.start, el.second);
    }

    return data;
}

#include "handler-document.h"
#include <QDebug>
#include <QList>
#include <QXmlStreamReader>
#include "docx-data.h"

QString handleTextRaplace(const QString& text) {

    QString handleText = QString("<m:r>"
                           "<m:rPr>"
                           "<m:sty m:val=\"p\" />"
                           "</m:rPr>"
                           "<w:rPr>"
                           "<w:rFonts w:ascii=\"Cambria Math\" w:eastAsia=\"Calibri\" w:hAnsi=\"Cambria Math\" w:cs=\"Tahoma\" />"
                           "<w:lang w:eastAsia=\"en-US\" />"
                           "</w:rPr>"
                           "<m:t>%1</m:t>"
                           "</m:r>"
                           ).arg(123.45);
    return handleText;
}

QString handler(QXmlStreamReader& xml) {
    bool isEnd = false;
    QString text = "";
    while(!(isEnd)) {
        QXmlStreamReader::TokenType tokenType = xml.readNext();
        QString nameTag = xml.name().toString();

        if(tokenType == QXmlStreamReader::StartElement && nameTag == "t") {
            text += xml.readElementText();
        }

        if (tokenType == QXmlStreamReader::EndElement && nameTag == "r") {
            isEnd = true;
        }
    }
    return text;
}

QList<QPair<StartEnd, QString>> HandlerDocument::handleoMath(QXmlStreamReader& xml) {
    QList<QPair<StartEnd, QString>> replaceTexts;
    bool isEnd = false;
    bool isTextReplace = false;// Для `{Nmax
    QString textReplace = "";//`{Nmax}`
    int startElementDelete = -1;
    int endElementDelete = -1;
    while(!(isEnd)) {
        int startElem = xml.characterOffset();
        QXmlStreamReader::TokenType tokenType = xml.readNext();
        QString nameTag = xml.name().toString();

        if (tokenType == QXmlStreamReader::StartElement && nameTag == "r") {
            QString pathText = handler(xml);

            //начало и конец
            switch(pathText.count('`')) {
            case 2:
                textReplace = pathText;
                isTextReplace = false;
                startElementDelete = startElem;
                break;
            case 1:
                isTextReplace = !isTextReplace;
                if (!isTextReplace){
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

            //todo: заменить текст
            if (textReplace != "" && !isTextReplace) {
                QString handleText = handleTextRaplace(textReplace);
                qDebug() << "textReplace:" <<textReplace;
                endElementDelete = xml.characterOffset();
                replaceTexts.append(QPair<StartEnd, QString> {{startElementDelete, endElementDelete}, handleText});
                textReplace = "";
            }

        }

        if (tokenType == QXmlStreamReader::EndElement && nameTag == "oMath") {
            isEnd = true;
        }
    }
    return replaceTexts;
}

QList<QPair<StartEnd, QString>> HandlerDocument::handleElements(QXmlStreamReader& xml) {
    QList<QPair<StartEnd, QString>> replaceTexts;
    QString name = xml.name().toString();
    if (name == "oMath") {
        replaceTexts.append(handleoMath(xml));
    } else if(name == "p") {
//        qDebug() << "p";
    }
    return replaceTexts;
}

QString HandlerDocument::handleDocument(const QString& rawData)
{
    QXmlStreamReader xml(rawData);
    QList<QPair<StartEnd, QString>> replaceTexts;

    while(!xml.atEnd()) {
        xml.readNext();
        if (xml.isStartElement()) {
             QList<QPair<StartEnd, QString>> replaceTexts_l = handleElements(xml);
             replaceTexts.append(replaceTexts_l);
        }
    }

    if (xml.hasError()) {
        qDebug() << "Ошибка чтения";
    }

    for(auto el : replaceTexts) {
        qDebug() << rawData.mid(el.first.start, el.first.end - el.first.start);
        qDebug() << el.second;
    }

    return rawData;
}

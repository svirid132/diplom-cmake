#include "handler-document.h"
#include <QDebug>
#include <QList>
#include <QXmlStreamReader>

HandlerDocument::HandlerDocument(){

}

void HandlerDocument::setInfo(const QString& rawData, DocData docData = DocData()){
    this->rawData = rawData;
    this->docData = docData;
}

QString HandlerDocument::handleMathRaplace(const QString& specSymb, Docx::Text specText) {

    QString text = "";
    if (docData.N0 != -1) {//Не тествовый режим!
        if (specSymbol.X == specSymb) {
            text = QString::number(docData.X);
        } else if(specSymbol.Y == specSymb) {
            text = QString::number(docData.Y);
        } else if (specSymbol.Z == specSymb) {
            text = QString::number(docData.Z);
        } else if (specSymbol.Xm == specSymb) {
            text = QString::number(docData.Xm);
        } else if (specSymbol.N0 == specSymb) {
            text = QString::number(docData.N0);
        } else if (specSymbol.Nmax == specSymb) {
            text = QString::number(docData.Nmax);
        } else if (specSymbol.Nmax_N0 == specSymb) {
            text = QString::number(docData.Nmax_N0);
        } else if (specSymbol.h == specSymb) {
            text = QString::number(docData.h);
        } else if (specSymbol.Xm_h == specSymb) {
            text = QString::number(docData.Xm_h);
        } else if(specSymbol.category == specSymb) {
            text = docData.category;
        }
    } else {
        if (specText & Docx::Text::num) {
            text = "1999";
        } else {
            text = "words";
        }
    }

    //Вставка спец текста
    QString xmlText = "";
    if (specText & Docx::Text::text) {
        xmlText = "<w:r w:rsidR=\"00CD17DF\" w:rsidRPr=\"00CD17DF\"><w:rPr><w:rFonts w:ascii=\"Tahoma\" w:hAnsi=\"Tahoma\" w:cs=\"Tahoma\"/>%2</w:rPr><w:t%1>%3</w:t></w:r>";

        if (specText & Docx::Text::textSpace) {
            xmlText = xmlText.arg(" xml:space=\"preserve\"");
        } else {
            xmlText = xmlText.arg("");
        }
        
        if (specText & Docx::Text::textBold) {
            xmlText = xmlText.arg("<w:b/>");
        } else {
            xmlText = xmlText.arg("");
        }
    } else if (Docx::Text::num) {
        xmlText = "<m:r><w:rPr><w:rFonts w:ascii="Cambria Math" w:eastAsia="Calibri" w:hAnsi="Cambria Math" w:cs="Tahoma" /><w:lang w:eastAsia="en-US" /></w:rPr><m:t>%1</m:t></m:r>";
    }

    xmlText = xmlText.arg(text);

    return xmlText;
}

QString HandlerDocument::handler(QXmlStreamReader& xml, bool& isSpace = false, bool& isBold = false) {
    bool isEnd = false;
    QString text = "";
    while(!(isEnd)) {
        QXmlStreamReader::TokenType tokenType = xml.readNext();
        QString nameTag = xml.name().toString();
        QXmlStreamAttributes attributes;

        if(tokenType == QXmlStreamReader::StartElement && nameTag == "t") {
            text += xml.readElementText();
            attributes = xml.attributes();
        }

        if ( attributes.hasAttribute("xml:space") ) {
            isSpace = true;
        }

        if(nameTag == "b") {
            isBold = true;
        }

        if (tokenType == QXmlStreamReader::EndElement && nameTag == "r") {
            isEnd = true;
        }
    }
    return text;
}

QList<QPair<StartEnd, QString>> HandlerDocument::handleText(QXmlStreamReader& xml) {
    QList<QPair<StartEnd, QString>> replaceTexts;
    bool isEnd = false;
    bool isTextReplace = false;// Для `{Nmax
    QString textReplace = "";//`{Nmax}`
    int startElementDelete = -1;
    int endElementDelete = -1;
    bool isBold = false;
    bool isSpace = false;
    while(!(isEnd)) {
        int startElem = xml.characterOffset();
        QXmlStreamReader::TokenType tokenType = xml.readNext();
        QString nameTag = xml.name().toString();

        if (tokenType == QXmlStreamReader::StartElement && nameTag == "r") {
            QString pathText = handler(xml, isSpace, isBold);
            QString prefix = xml.prefix().toString();

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

            //TODO: заменить текст
            if (textReplace != "" && !isTextReplace) {
                QString trimmedText = textReplace.trimmed();
                Docx::Text specText;
                if (prefix == "m") {
                    specText = Docx::Text::text;
                } else {
                    specText = Docx::Text::num;
                } 
                if (isBold) specText = specText | Docx::Text::textBold;
                if (isSpace) specText = specText | Docx::Text::textSpace;
                QString handleText = handleMathRaplace(trimmedText, specText);
                endElementDelete = xml.characterOffset();
                replaceTexts.append(QPair<StartEnd, QString> {{startElementDelete, endElementDelete}, handleText});
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

QList<QPair<StartEnd, QString>> HandlerDocument::handleElements(QXmlStreamReader& xml) {
    QList<QPair<StartEnd, QString>> replaceTexts;
    QString name = xml.name().toString();
    if (name == "p") {
        auto result = handleText(xml);
        replaceTexts.append(result);
    }

    return replaceTexts;
}

QString HandlerDocument::handleDocument()
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

    QString data = rawData;
    for(int i = replaceTexts.count() - 1; i > -1; --i) {
        auto el = replaceTexts.at(i);
        QString textReplace = data.mid(el.first.start, el.first.end - el.first.start);
        data.remove(el.first.start, el.first.end - el.first.start);
        data.insert(el.first.start, el.second);
//        qDebug() << textReplace << Qt::endl << data.indexOf(textReplace) << Qt::endl
//                 << el.second << Qt::endl << el.first.start << el.first.end << Qt::endl;
    }

    return data;
}

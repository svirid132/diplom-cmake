#include "handler-document.h"
#include <QDebug>
#include <QList>
#include <QXmlStreamReader>

HandlerDocument::HandlerDocument(){

}

void HandlerDocument::setInfo(const QString& rawData, DocData docData){
    this->rawData = rawData;
    this->docData = docData;
}

QString HandlerDocument::handleMathRaplace(const QString& specSymb) {

    QString text = "";
    bool words = false;
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
        words = true;
        text = docData.category;
    }

    QString handleText =
        words ?
            QString("<w:r w:rsidR=\"00CD17DF\" w:rsidRPr=\"00CD17DF\"><w:rPr><w:rFonts w:ascii=\"Tahoma\" w:hAnsi=\"Tahoma\" w:cs=\"Tahoma\"/></w:rPr><w:t xml:space=\"preserve\">%1 </w:t></w:r>").arg(text) :
            QString("<m:r><w:rPr><w:rFonts w:ascii=\"Cambria Math\" w:eastAsia=\"Calibri\" w:hAnsi=\"Cambria Math\" w:cs=\"Tahoma\" /><w:lang w:eastAsia=\"en-US\" /></w:rPr><m:t>%1</m:t></m:r>").arg(text);

    return handleText;
}

QString HandlerDocument::handler(QXmlStreamReader& xml) {
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

QList<QPair<StartEnd, QString>> HandlerDocument::handleText(QXmlStreamReader& xml) {
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
                QString trimmedText = textReplace.trimmed();
                QString handleText = handleMathRaplace(trimmedText);
                endElementDelete = xml.characterOffset();
                replaceTexts.append(QPair<StartEnd, QString> {{startElementDelete, endElementDelete}, handleText});
                textReplace = "";
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

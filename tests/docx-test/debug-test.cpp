//
// Created by sviri on 09.03.2022.
//

#include <QDebug>
#include <QtCore/QProcess>
#include <QtCore/QCoreApplication>
//#include <windows.h>
#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include <docx.h>
#include "debug-config.h"
#include "data-docx-test.h"

int main(int argc, char *argv[]) {


    DocData docData = getDocData();
    QList<QPointF> glub_nimp = getGlub_Nimp();
    QPointF criticalPoint = getCriticalPoint();

    Docx docx;
    docx.setData(docData, glub_nimp, criticalPoint);
    docx.create("created.docx");

    QFile file("created.docx");
    qDebug() << "open file:" << file.open(QIODevice::ReadOnly);

    //Bad idea
    if (SAVE_REALES_ASSETS) {
        qDebug() << PATH_SOURCE_ASSETS;
    }

    //open created docx
    if (RUN_REALES_DOCX) {
        QProcess process;
        QFileInfo info(file);
        process.start("cmd",
                      QStringList() << "/C" << info.filePath());
        process.waitForFinished();
    }

    return 0;
}

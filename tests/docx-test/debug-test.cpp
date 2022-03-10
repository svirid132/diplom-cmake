//
// Created by sviri on 09.03.2022.
//

#include <QDebug>
#include <QtCore/QProcess>
#include <QtCore/QCoreApplication>
#include <windows.h>
#include <QtCore/QFile>
#include <QtCore/QFileInfo>

#include "docx-data-test.h"

int main(int argc, char *argv[]) {


    DocData docData = getDocData();

    QFile file(":/template.docx");
    QFileInfo info(file);
    qDebug() << file.open(QIODevice::ReadOnly);
    QProcess process;
    process.start("cmd" ,
            QStringList() << "/C" << info.filePath());
    //"D:\\Project\\diplom\\diplom-cmake\\TODO\\modif\\template-0.4-modif-replace.docx"
    qDebug() << info.filePath();

    process.waitForFinished();

    return 0;
}

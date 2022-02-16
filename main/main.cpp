#include "UI/mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QVector>
#include <limits>
#include "rawfile.h"
#include "smath.h"
#include "math-logic.h"
#include "preloader.h"
#include <exception> // для std::exception
#include <iostream>
#include "error.h"
#include "xmlfile.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    preloader(w);
    w.show();

//    QPair<QString, QString> pair = {"sring", "123"};
//    qDebug() << pair.first << pair.second;

//    QList<QPair<QString, QString>> list;
//    list.append(pair);
//    XMLFile::write("123.xml", list);

    return a.exec();
}

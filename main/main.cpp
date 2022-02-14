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

QString str() {
    throw ErrorFile::open();
    return "my-str";
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    preloader(w);
    w.show();

    return a.exec();
}

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
#include <docx.h>
#include <exception> // для std::exception
#include <iostream>
#include <XMLtoDOCX.h>
#include <UI/DialogConverter.h>
#include "error.h"
#include "xmlfile.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    //release
    preloader(w);
    w.show();

    return a.exec();
}

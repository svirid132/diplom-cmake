//
// Created by Пользователь on 16.03.2022.
//

#ifndef DIPLOM_CMAKE_INITDIALOGCONVERTER_H
#define DIPLOM_CMAKE_INITDIALOGCONVERTER_H


#include <functional>
#include <mainwindow.h>
#include "preloader-var.h"

//return docxPath
std::function<QString(const DialogParam& param, const QString& docxPath, bool& ok)> initDialogConverter(MainWindow& window, const QString& dirDocx);

#endif //DIPLOM_CMAKE_INITDIALOGCONVERTER_H

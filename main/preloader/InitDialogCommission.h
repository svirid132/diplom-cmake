//
// Created by sviri on 11.03.2022.
//

#ifndef DIPLOM_CMAKE_INITDIALOGCOMMISSION_H
#define DIPLOM_CMAKE_INITDIALOGCOMMISSION_H

#include <functional>
#include "../UI/mainwindow.h"
#include "UI-var.h"
#include "DialogCommission.h"
#include "preloader-var.h"

std::function<DataCommission(const DialogParam& param, const DataCommission& data, bool& ok)> initDialogCommission(MainWindow& window);

#endif //DIPLOM_CMAKE_INITDIALOGCOMMISSION_H

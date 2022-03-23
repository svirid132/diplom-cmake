//
// Created by sviri on 23.03.2022.
//

#ifndef DIPLOM_CMAKE_SETTINGSUI_H
#define DIPLOM_CMAKE_SETTINGSUI_H


#include <QtWidgets/QSpinBox>
#include <QtWidgets/QDateTimeEdit>

namespace SettingsUI {
    void spinBox(QSpinBox* wid);
    void doubleSpinBox(QDoubleSpinBox* wid);
    void dateTimeEdit(QDateTimeEdit* wid);
}

#endif //DIPLOM_CMAKE_SETTINGSUI_H

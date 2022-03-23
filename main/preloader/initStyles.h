//
// Created by sviri on 23.03.2022.
//

#ifndef DIPLOM_CMAKE_INITSTYLES_H
#define DIPLOM_CMAKE_INITSTYLES_H

#include <QtWidgets/QSpinBox>
#include <QtWidgets/QDateTimeEdit>

namespace SettingsUI {
    void spinBox(QSpinBox* wid);
    void doubleSpinBox(QDoubleSpinBox* wid);
    void dateTimeEdit(QDateTimeEdit* wid);
    QString getStylesheet(const QString& dirPath);
}

#endif //DIPLOM_CMAKE_INITSTYLES_H

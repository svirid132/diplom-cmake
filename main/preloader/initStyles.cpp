//
// Created by sviri on 23.03.2022.
//

#include <QtCore/QDir>
#include "initStyles.h"

void SettingsUI::spinBox(QSpinBox* wid) {

    wid->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}

void SettingsUI::doubleSpinBox(QDoubleSpinBox *wid) {
    wid->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}

void SettingsUI::dateTimeEdit(QDateTimeEdit* wid) {
    wid->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}

QString SettingsUI::getStylesheet(const QString &dirPath) {
    QDir dir(dirPath);
    if(!dir.exists()) return "";

    QString final = "";
    QFileInfoList infoList = dir.entryInfoList(QStringList({"*.qss"}), QDir::Files);
    for (auto fileInfo: infoList) {
        QFile file(fileInfo.absoluteFilePath());
        if(file.open(QIODevice::ReadOnly)) {
            QString path = QString::fromUtf8(file.readAll());
            final += path;
        }
    }
    return final;
}
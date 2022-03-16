//
// Created by Пользователь on 15.03.2022.
//

#include <QtCore/QDir>
#include "FileSystem.h"


void FileSystems::mkdirDirFiles() {
    QDir dir = QDir(QDir::currentPath());
    QString dirFiles = FileSystems::dirFiles;
    if (!dir.exists(dirFiles)) {
        if (!dir.mkdir(dirFiles)) return;
    }
}

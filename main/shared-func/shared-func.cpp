#include <QtCore/QFileInfo>
#include "shared-func.h"

QString getCategoryString(const CATEGORY& category) {
    QString string;
    switch(category) {
        case CATEGORY::PERILOUSLY:
            string = "ОПАСНО";
            break;
        case CATEGORY::SAFELY:
            string = "НЕОПАСНО";
    }
    return string;
}

bool isFileExists(const QString& path) {
    QFileInfo fileInfo;
    fileInfo.setFile(path);
    return fileInfo.exists();
}
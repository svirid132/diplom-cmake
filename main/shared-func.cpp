#include "shared-func.h"

QString getCategoryString(const CATEGORY& category) {
    QString string;
    switch(category) {
        case CATEGORY::PERILOUSLY:
            string = "Опасно";
            break;
        case CATEGORY::SAFELY:
            string = "Неопасно";
    }
    return string;
}

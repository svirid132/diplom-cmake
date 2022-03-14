//
// Created by Пользователь on 14.03.2022.
//

#include "XMLtoDOCX.h"

XMLtoDOCX::XMLtoDOCX() {

}

void XMLtoDOCX::setPathXML(const QString &path) {
    xmlPath = path;
}

void XMLtoDOCX::setPathDocx(const QString &path) {
    docxPath = path;
}

bool XMLtoDOCX::handle() {

    return false;
}

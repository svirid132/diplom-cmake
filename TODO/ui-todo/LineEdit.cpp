//
// Created by Пользователь on 23.03.2022.
//

#include "LineEdit.h"

LineEdit::LineEdit(QWidget *parent) : QLineEdit(parent) {

}

LineEdit::LineEdit(const QString &text, QWidget *parent) : QLineEdit(text, parent) {

}

void LineEdit::paintEvent(QPaintEvent *event) {
    QLineEdit::paintEvent(event);


}

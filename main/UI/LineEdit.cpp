//
// Created by Пользователь on 23.03.2022.
//

#include <QtGui/QPainter>
#include "LineEdit.h"
#include <QDebug>
#include <QMouseEvent>
#include <QTimer>

LineEdit::LineEdit(QWidget *parent) : QLineEdit(parent), isOver(false) {
    setMouseTracking(true);
}

LineEdit::LineEdit(const QString &text, QWidget *parent) : QLineEdit(text, parent), isOver(false) {
    setMouseTracking(true);
}

void LineEdit::paintEvent(QPaintEvent *event) {
    QLineEdit::paintEvent(event);

    QPainter painter(this);
    const float y = (height() - fontInfo().pixelSize()) / 2 + fontInfo().pixelSize() + 1.5;
    QPointF start(10, y);
    QPointF end(width() - 10, y);
    if (isOver || hasFocus()) {
        QPen pen = QColor("#34D5EB");
        pen.setWidth(2);
        painter.setPen(pen);
    } else {
        QPen pen = QColor("#C4C4C4");
        pen.setWidth(2);
        painter.setPen(pen);
    }
    painter.drawLine(QLineF(start, end));

}

void LineEdit::mouseReleaseEvent(QMouseEvent *event) {
    QLineEdit::mouseReleaseEvent(event);

    isOver = false;
}

void LineEdit::enterEvent(QEvent *event) {
    QWidget::enterEvent(event);

    isOver = true;
}

void LineEdit::leaveEvent(QEvent *event) {
    QWidget::leaveEvent(event);

    isOver = false;
}

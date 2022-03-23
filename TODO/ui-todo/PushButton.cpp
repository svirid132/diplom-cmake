//
// Created by Пользователь on 22.03.2022.
//

#include <QtGui/QPainter>
#include <QtCore/QDebug>
#include "PushButton.h"
#include <QPointF>
#include <QtSvg/QSvgGenerator>
#include <QtSvg/QSvgRenderer>

PushButton::PushButton(QWidget *parent) :
        QPushButton(parent),
        sizeIcon(QSize(24, 24)) {

    const int fontPixel = 16;//px
    font.setPixelSize(fontPixel);
}

PushButton::PushButton(const QString &text, QWidget *parent) :
        QPushButton(parent),
        sizeIcon(QSize(24, 24)) {

    const int fontPixel = 16;//px
    font.setPixelSize(fontPixel);
    this->text = text;
    resize(sizeHint());
}

PushButton::~PushButton() {
}

void PushButton::setText(const QString &text) {

    this->text = text;

    resize(sizeHint());
}


QSize PushButton::sizeHint() const {
    const auto parentHint = QPushButton::sizeHint();
    // add margins here if needed

    QFontMetrics fm(font);
    int textWide = fm.horizontalAdvance(text);
    const int iconWide = sizeIcon.width();

    const int width = textWide + iconWide + padding.width();
    const int height = std::max(parentHint.height(), sizeIcon.height());

    return QSize(width, height);
}

void PushButton::paintEvent(QPaintEvent *e) {
    QPushButton::paintEvent(e);

    QPainter painter(this);
    painter.setFont(font);
    QSize size = QSize(width(), height());

    if (!isError) {
        QRect textRect(0, 0, size.width(), size.height());
        painter.drawText(textRect, Qt::AlignHCenter | Qt::AlignVCenter, text);
    } else {

        const int rectW = size.width();
        const int textax = padding.left;
        QRect textRect(textax, 0, rectW, size.height());
        painter.drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, text);

        const int y = (height() - sizeIcon.height()) / 2; // add margin if needed
        const int paddingFromText = padding.rigth - 5;
        const int x = size.width() - sizeIcon.width() - paddingFromText;
        QPointF pointIcon(x, y);
        QSvgRenderer svgRenderer(QString(":/error.svg"));
        svgRenderer.render(&painter, QRectF(pointIcon, sizeIcon));
    }

    painter.end();
}

void PushButton::error() {
    isError = true;
}

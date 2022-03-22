//
// Created by Пользователь on 22.03.2022.
//

#include <QtGui/QPainter>
#include <QtCore/QDebug>
#include "PushButton.h"
#include <QPointF>
#include <QtSvg/QSvgGenerator>
#include <QtSvg/QSvgRenderer>

PushButton::PushButton(QWidget* parent) :
    QPushButton(parent),
    sizeSvg(24, 24)
{
    const int fontPixel = 16;//px
    font.setPixelSize(fontPixel);
}

PushButton::PushButton(const QString &text, QWidget *parent) : QPushButton(parent) {

    const int fontPixel = 16;//px
    font.setPixelSize(fontPixel);

    this->text = text;
}

PushButton::~PushButton()
{
}

void PushButton::setText(const QString& text) {

    this->text = text;

    resize(sizeHint());
}


QSize PushButton::sizeHint () const
{
    const auto parentHint = QPushButton::sizeHint();
    // add margins here if needed

    QFontMetrics fm(font);
    int pixelsWide = fm.horizontalAdvance(text);
    const int iconWide = sizeSvg.width();

    const int width = pixelsWide + iconWide + paddingW;
    const int height = std::max(parentHint.height(), sizeSvg.height());

    return QSize(width, height);
}

void PushButton::paintEvent(QPaintEvent* e)
{
    QPushButton::paintEvent(e);

    qDebug() << sizeHint().height() << height();

    QPainter painter(this);

    painter.setFont(font);

    if (!isError) {
        QRect textRect(0, 0, sizeHint().width(), sizeHint().height());
        painter.drawText(textRect, Qt::AlignHCenter | Qt::AlignVCenter, text);
        painter.drawLine(QPointF(0, 10), QPointF(sizeHint().width(), 10));
    } else {

        const int rectW = sizeHint().width();
        const int textax = paddingW / 2;
        QRect textRect(textax, 0, rectW, sizeHint().height());
        painter.drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, text);

        QSize sizeSvg(24, 24);
        const int y = (height() - sizeSvg.height()) / 2; // add margin if needed
        const int paddingRIcon = 10;
        const int x = sizeHint().width() - sizeSvg.width() - paddingRIcon;
        QPointF pointSvg(x, y);
        QSvgRenderer svgRenderer(QString(":/error.svg"));
        svgRenderer.render(&painter, QRectF(pointSvg, sizeSvg));
    }

    painter.end();
}

void PushButton::error() {
    isError = true;
}

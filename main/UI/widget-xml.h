#ifndef WIDGETXML_H
#define WIDGETXML_H

#include <QDateEdit>
#include <QWidget>
#include "UI/UI-var.h"

class WidgetXML : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetXML(QWidget *parent = nullptr);
    DataWgtXML getData();

private:
    QDate date;
    QString rudnik;
    QString nameVirab;
    QString izmVip;
    int XX;
    int YY;
    int ZZ;

signals:
    void clickedSave();
};

#endif // WIDGETXML_H

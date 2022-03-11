#ifndef WIDGETXML_H
#define WIDGETXML_H

#include <QDateEdit>
#include <QWidget>
#include <QtWidgets/QPushButton>
#include "UI-var.h"

class WidgetXML : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetXML(QWidget *parent = nullptr);
    DataWgtXML getData();
    void errorCommission();

private:
    QDate date;
    QString rudnik;
    QString nameVirab;
    QString izmVip;
    int XX;
    int YY;
    int ZZ;

    QPushButton* btnCommission;

signals:
    void clickedSave();
    void createDocx();
    void clickedCommission();
};

#endif // WIDGETXML_H

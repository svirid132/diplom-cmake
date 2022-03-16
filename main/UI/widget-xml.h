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
    double XX;
    double YY;
    double ZZ;

    QPushButton* btnCommission;

signals:
    void clickedSave();
    void createDocx();
    void clickedCommission();
    void clickedXmlToDocx();
};

#endif // WIDGETXML_H

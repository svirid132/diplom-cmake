//
// Created by Пользователь on 10.03.2022.
//

#ifndef DIPLOM_CMAKE_DIALOGCOMMISSION_H
#define DIPLOM_CMAKE_DIALOGCOMMISSION_H


#include <QtWidgets/QDialog>
#include "UI-var.h"

class DialogCommission : public QDialog {

    Q_OBJECT
public:
    explicit DialogCommission(QWidget *parent = nullptr);

    DataCommission getDataCommission();
    void setDataCommission(const DataCommission &data);

public slots:
    void acceptSlot();

private:
    QList<QWidget*> inputWidget;

    void adjustInputWidget();

    DataCommission dataCommission;
    //name object
    const QString nameWritter = "nameWritter";
    const QString posDescWritter = "posDescWritter";
    const QString nameMain = "nameMain";
    const QString posDescMain = "posDescMain";
    const QString nameMembOne = "nameMembOne";
    const QString posDescMembOne = "posDescMembOne";
    const QString nameMembTwo = "nameMembTwo";
    const QString posDescMembTwo = "posDescMembTwo";

    QString handlePos(const QString& name, const QString& pos);
};


#endif //DIPLOM_CMAKE_DIALOGCOMMISSION_H

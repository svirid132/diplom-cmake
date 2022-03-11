#ifndef UIVAR_H
#define UIVAR_H

#include <QDate>
#include <QString>
#include <QMetaType>

struct DataWgtXML {
    QDate date;
    QString rudnik;
    QString nameVirab;
    QString izmVip;
    int XX;
    int YY;
    int ZZ;
};

struct DataCommission {
    QString nameWritter = "-1";//for isDataCommission
    QString posDescWritter;
    QString nameMain;
    QString posDescMain;
    QString nameMembOne;
    QString posDescMembOne;
    QString nameMembTwo;
    QString posDescMembTwo;
};

Q_DECLARE_METATYPE(DataCommission)

#endif // UIVAR_H

#ifndef API_var_H
#define API_var_H

#include <QtCore/QString>
#include <QList>

struct CountOverAmps {
    int countAmps;
    int period;
};

struct XmlData {
    QString Date;
    QString rudnik;
    QList<int> imps;
    float Xm;
    float Lsh;
    float h;
    int N0 = -1;
    int Nmax;
    float X;
    float Y;
    float Z;
    QString product;
    QString person;
    float koefZap;
    QString category;
};

#endif // GLOBALVAR_H

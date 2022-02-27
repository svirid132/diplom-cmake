#ifndef DOCXDATA_H
#define DOCXDATA_H

#include <QString>

struct StartEnd {
    int start;
    int end;
};

struct DocData {
    int Nmax;
    int N0;
    float Nmax_N0;
    float Xm;
    float h;
    float Xm_h;
    QString category = "";
    float X;
    float Y;
    float Z;
};

#endif // DOCXDATA_H

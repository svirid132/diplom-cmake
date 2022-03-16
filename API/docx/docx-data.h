#ifndef DOCXDATA_H
#define DOCXDATA_H

#include <QString>

struct StartEnd {
    int start;
    int end;
};

struct DocCommission {
    QString posDescWritter;
    QString nameWritter;
    QString nameMain;
    QString posDescMain;
    QString nameMembOne;
    QString posDescMembOne;
    QString nameMembTwo;
    QString posDescMembTwo;
};

struct DocData {
    DocCommission docCommission;
    QString product;
    QString dateProduct;
    QString rudnik;
    int Nmax;
    int N0 = -1;
    float Nmax_N0;
    float Xm;
    float h;
    float Xm_h;
    QString category = "";
    float X;
    float Y;
    float Z;
    float koefZap;
    QString year;
};

namespace DocxFlags {
    enum Text {
        textBold = 0x1,
        textSpace = 0x10,
        text = 0x100,
        num = 0x1000,
    };
    Q_DECLARE_FLAGS(Texts, Text)
};

#endif // DOCXDATA_H

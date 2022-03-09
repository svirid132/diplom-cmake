#ifndef DOCXDATA_H
#define DOCXDATA_H

#include <QString>

struct StartEnd {
    int start;
    int end;
};

struct DocData {
    QString posDescWritter;
    QString nameWritter;
    QString product;
    QString dataProduct;
    QString posDescMain;
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
};

namespace Docx {
    enum Text {
        textBold = 0x1,
        textSpace = 0x10,
        text = 0x100,
        num = 0x1000,
    }
}

#endif // DOCXDATA_H

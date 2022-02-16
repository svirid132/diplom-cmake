#include "math-logic.h"

#include <QDebug>
#include <cmath>

MathLogic::MathLogic()
{

}

QPointF MathLogic::getCriticalPoint() { return criticalPoint; }

float MathLogic::getKoefZap() { return koefZap; }

QVector<QPointF> MathLogic::getGlub_Nimp() { return glub_Nimp; }

CATEGORY MathLogic::getCategory() {
    return category;
}

QVector<CountOverAmps> MathLogic::getNimp()
{
    return Nimp;
}

void MathLogic::calc(const QVector<CountOverAmps> &Nimp, float Lsh, float h) {
    this->Lsh = Lsh;
    this->h = h;
    this->Nimp = Nimp;
    Nmax_N0 = caclNmax_N0(Nimp);
    QVector<float> glub = calcGlub(Lsh, Nimp.size());
    QVector<QPointF> Nimp_Glub = calcGlub_Nimp(glub, Nimp);
    X1 = calcX1(Nimp_Glub);
    X1_h = caclX1_h(X1, h);
    criticalPoint = calcCriticalPoint(X1_h, Nmax_N0);
    koefZap = calcKoefZap(X1_h, Nmax_N0);
    glub_Nimp = calcGlub_Nimp(glub, Nimp);
    category = calcCategory(X1_h, Nmax_N0);
}

CATEGORY MathLogic::calcCategory(float X1_h, float Nmax_N0) {
    float indexCategory = float(4.8) * std::pow(X1_h, 3) +
            float(14.0229) * std::pow(X1_h, 2) -
            float(1.5029) * X1_h +
            float(7.3129);
    return Nmax_N0 > indexCategory ? CATEGORY::PERILOUSLY : CATEGORY::SAFELY;
}


QVector<float> MathLogic::calcGlub(float Lsh, int Nizm) {
    int Nint = Nizm - 1;
    float shag = float(Lsh)/ float(Nint);
    QVector<float> glub;
    glub.append(0);
    for (int i = 0; i < Nint; ++i) {
        float newGlub = glub[i] + shag;
        glub.append(newGlub);
    }
    return glub;
}

float MathLogic::calcX1(QVector<QPointF> Nimp_Glub) {
    float maxNimp = 0;
    float X1 = 0;
    for (int i = 0; i < Nimp_Glub.size(); ++i) {
        if (maxNimp < Nimp_Glub[i].y()) {
            maxNimp = Nimp_Glub[i].y();
            X1 = Nimp_Glub[i].x();
        }
    }
    return X1;
}

float MathLogic::caclX1_h(float X1, float h) { return X1 / h; }

float MathLogic::caclNmax_N0(QVector<CountOverAmps> Nimp) {
    Nmax = 0;
    for (int i = 0; i < Nimp.size(); ++i){
        if (Nimp[i].countAmps > Nmax) {
            Nmax = Nimp[i].countAmps;
        }
    }
    N0 = Nimp[0].countAmps;
    float Nmax_N0 = float(Nmax) / float(N0);
    return Nmax_N0;
}

float MathLogic::calcKoefZap(float X1_h, float Nmax_N0){
    float koefZap =
            (float(4.8)*std::pow(X1_h, 3) +
             float(14.0229)*pow(X1_h, 2) -
             float(1.5029) * X1_h +
             float(7.3129)) / Nmax_N0;
    return koefZap;
}

QVector<QPointF> MathLogic::calcGlub_Nimp(const QVector<float> &glub, const QVector<CountOverAmps> &Nimp){
    QVector<QPointF> glub_Nimp;
    for (int i = 0; i < Nimp.size(); ++i) {
        QPointF point;
        point.setX( qreal(glub[i]) );
        point.setY( qreal(Nimp[i].countAmps) );
        glub_Nimp.append(point);
    }
    return glub_Nimp;
}

QPointF MathLogic::calcCriticalPoint(float X1_h, float Nmax_N0){
    QPointF point = {X1_h, Nmax_N0};
    return point;
}

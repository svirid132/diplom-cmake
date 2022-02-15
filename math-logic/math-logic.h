#ifndef MATHLOGIC_H
#define MATHLOGIC_H

#include <smath.h>
#include <QList>
#include <QString>
#include "API-var.h"
#include "math-var.h"

#include <QDebug>
#include <QPointF>
#include <cmath>

class MathLogic {
public:
    MathLogic();

    void calc(const QVector<CountOverAmps>& Nimp, float Lsh, float h);

    static QVector<QPointF> getDefaultPoints(int count = 20) {
        QVector<QPointF> points;
        for (int i = 0; i < count; ++i) {
            float X1_0h = 0.05 * i;
            float Nmax_N0 =
                    4.8 * std::pow(X1_0h, 3) +
                    14.0229 * std::pow(X1_0h, 2) -
                    1.5029 * X1_0h + 7.3129;
            QPointF point = {X1_0h, Nmax_N0};
            points.append(point);
        }
        return points;
    };

    QPointF getCriticalPoint();
    float getKoefZap();
    QVector<QPointF> getGlub_Nimp();
    CATEGORY getCategory();
    QVector<CountOverAmps> getNimp();
private:
    QVector<CountOverAmps> Nimp;
    QPointF criticalPoint;
    float koefZap;
    QVector<QPointF> glub_Nimp;
    CATEGORY category;

    QVector<float> calcGlub(float Lsh, int Nizm);
    float calcX1(QVector<QPointF> Nimp_Glub);
    float caclX1_h(float X1, float h);
    float caclNmax_N0(QVector<CountOverAmps> Nimp);
    float calcKoefZap(float X1_h, float Nmax_N0);
    QVector<QPointF> calcGlub_Nimp(const QVector<float> &glub, const QVector<CountOverAmps>& Nimp);
    //x = X1_h y = Nmax_N0
    QPointF calcCriticalPoint(float X1_h, float Nmax_N0);
    CATEGORY calcCategory(float X1_h, float Nmax_N0);;
};

#endif // MATHLOGIC_H

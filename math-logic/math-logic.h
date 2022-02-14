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
    //x = X1_h y = Nmax_N0
    static QPointF getCriticalPoint(QVector<CountOverAmps> Nimp, float Lsh, float h){
        float Nmax_N0 = handleNmax_N0(Nimp);
        QVector<float> Glub = handleGlub(Lsh, Nimp.size());
        QVector<QPointF> Nimp_Glub = handleGlub_Nimp(Nimp, Glub);
        float X1 = handleX1(Nimp_Glub);
        float X1_h = handleX1_h(X1, h);
//        float X1_h_toch = X1_h * 20 + 1;
        QPointF point = {X1_h, Nmax_N0};
        return point;
    };
    static float getKoefZap(QVector<CountOverAmps> Nimp, float Lsh, float h){
        float Nmax_N0 = handleNmax_N0(Nimp);
        QVector<float> Glub = handleGlub(Lsh, Nimp.size());
        QVector<QPointF> Nimp_Glub = handleGlub_Nimp(Nimp, Glub);
        float X1 = handleX1(Nimp_Glub);
        float X1_h = handleX1_h(X1, h);
        float koefZap =
                (float(4.8)*std::pow(X1_h, 3) +
                 float(14.0229)*pow(X1_h, 2) -
                 float(1.5029) * X1_h +
                 float(7.3129)) / Nmax_N0;
        return koefZap;
    };
    static QVector<QPointF> getGlub_Nimp(const QVector<CountOverAmps>& Nimp, float Lsh){
        QVector<float> Glub = handleGlub(Lsh, Nimp.size());
        QVector<QPointF> Nimp_Glub = handleGlub_Nimp(Nimp, Glub);
        return Nimp_Glub;
    };
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
    static CATEGORY getCategory(const QVector<CountOverAmps>& Nimp, float Lsh, float h) {
        float Nmax_N0 = handleNmax_N0(Nimp);
        QVector<float> Glub = handleGlub(Lsh, Nimp.size());
        QVector<QPointF> Nimp_Glub = handleGlub_Nimp(Nimp, Glub);
        float X1 = handleX1(Nimp_Glub);
        float X1_h = handleX1_h(X1, h);
        float indexCategory = float(4.8) * std::pow(X1_h, 3) +
                float(14.0229) * std::pow(X1_h, 2) -
                float(1.5029) * X1_h +
                float(7.3129);
        return Nmax_N0 > indexCategory ? CATEGORY::PERILOUSLY : CATEGORY::SAFELY;
    };
protected:
    static QVector<float> handleGlub(float Lsh, int Nizm) {
        int Nint = Nizm - 1;
        float shag = float(Lsh)/ float(Nint);
        QVector<float> glub;
        glub.append(0);
        for (int i = 0; i < Nint; ++i) {
            float newGlub = glub[i] + shag;
            glub.append(newGlub);
        }
        return glub;
    };
    static QVector<QPointF> handleGlub_Nimp(QVector<CountOverAmps> Nimp, QVector<float> Glub) {
        QVector<QPointF> points;
        for (int i = 0; i < Nimp.size(); ++i) {
            QPointF point;
            point.setX( qreal(Glub[i]) );
            point.setY( qreal(Nimp[i].countAmps) );
            points.append(point);
        }
        return points;
    };
    static float handleX1(QVector<QPointF> Nimp_Glub) {
        float maxNimp = 0;
        float X1 = 0;
        for (int i = 0; i < Nimp_Glub.size(); ++i) {
            if (maxNimp < Nimp_Glub[i].y()) {
                maxNimp = Nimp_Glub[i].y();
                X1 = Nimp_Glub[i].x();
            }
        }
        return X1;
    };
    static float handleX1_h(float X1, float h) { return X1 / h; };
    static float handleNmax_N0(QVector<CountOverAmps> Nimp) {
        int Nmax = 0;
        for (int i = 0; i < Nimp.size(); ++i){
            if (Nimp[i].countAmps > Nmax) {
                Nmax = Nimp[i].countAmps;
            }
        }
        float Nmax_N0 = float(Nmax) / float(Nimp[0].countAmps);
        return Nmax_N0;
    };
};

#endif // MATHLOGIC_H

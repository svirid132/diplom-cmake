#ifndef MATHLOGIC_H
#define MATHLOGIC_H

#include <QList>
#include <QString>
#include "API-var.h"
#include "math-var.h"

#include <QDebug>
#include <cmath>
#include "smath.h"

class MathLogic {
public:
    static Point getCriticalPoint(QVector<CountOverAmps> Nimp, float h, float Lsh){
        float Nmax_N0 = handleNmax_N0(Nimp);
        QVector<float> Glub = handleGlub(Lsh, Nimp.size());
        QVector<Point> Nimp_Glub = handleNimp_Glub(Nimp, Glub);
        float X1 = handleX1(Nimp_Glub);
        float X1_h = handleX1_h(X1, h);
        float X1_h_toch = X1_h * 20 + 1;
        Point point = {Nmax_N0, X1_h_toch};
        qDebug() << Nmax_N0 << X1 << X1_h << X1_h_toch;
        return point;
    };
    static float getKoefZap(QVector<CountOverAmps> Nimp, float h, float Lsh){
        float Nmax_N0 = handleNmax_N0(Nimp);
        QVector<float> Glub = handleGlub(Lsh, Nimp.size());
        QVector<Point> Nimp_Glub = handleNimp_Glub(Nimp, Glub);
        float X1 = handleX1(Nimp_Glub);
        float X1_h = handleX1_h(X1, h);
        float koefZap =
                (float(4.8)*std::pow(X1_h, 3) +
                 float(14.0229)*pow(X1_h, 2) -
                 float(1.5029) * X1_h +
                 float(7.3129)) / Nmax_N0;
        return koefZap;
    };
    static QVector<Point> getNimp_Glub(QVector<CountOverAmps> Nimp, float Lsh){
        QVector<float> Glub = handleGlub(Lsh, Nimp.size());
        QVector<Point> Nimp_Glub = handleNimp_Glub(Nimp, Glub);
        return Nimp_Glub;
    };
    static QVector<Point> getDefaultPoints(int count = 20) {
        QVector<Point> points;
        for (int i = 0; i < count; ++i) {
            float X1_0h = 0.05 * i;
            float Nmax_N0 =
                    4.8 * std::pow(X1_0h, 3) +
                    14.0229 * std::pow(X1_0h, 2) -
                    1.5029 * X1_0h + 7.3129;
            points.append(Point({Nmax_N0, X1_0h}));
        }
        return points;
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
            qDebug() << newGlub << shag << Nint;
        }
        return glub;
    };
    static QVector<Point> handleNimp_Glub(QVector<CountOverAmps> Nimp, QVector<float> Glub) {
        QVector<Point> points;
        for (int i = 0; i < Nimp.size(); ++i) {
            Point point;
            point.y = Nimp[i].countAmps;
            point.x = Glub[i];
            points.append(point);
        }
        return points;
    };
    static float handleX1(QVector<Point> Nimp_Glub) {
        float maxNimp = 0;
        float X1 = 0;
        for (int i = 0; i < Nimp_Glub.size(); ++i) {
            if (maxNimp < Nimp_Glub[i].y) {
                maxNimp = Nimp_Glub[i].y;
                X1 = Nimp_Glub[i].x;
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

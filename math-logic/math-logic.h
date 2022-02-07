#ifndef MATHLOGIC_H
#define MATHLOGIC_H

#include <QString>

struct CriticalPoint {
    float X1Onh;
    float NmaxOnN0;
};

struct ConstLists {
    float* constList_X1Onh;
    float* constList_NmaxOnN0;
    int length;
};

struct CalculedLists {
    float* depths;
    float* impulses;
    int length;
};

struct CalculedVals {
    ConstLists constList;
    CalculedLists calcList;
    CriticalPoint criticalPoint;
    float X1Onh;
    QString category;
    int N0;// 1 impulse
    int Nmax;// maxImpulse
    float NmaxOnN0;
    float strockRation;////Коэффицент запаса
};

class MathLogic {
public:
    static float findXFromMaxY(const float* Xs, const float* Ys, int length);
    static float calcStrockRation(float Lsh, float h, float Nmax, float N0);
    static CriticalPoint calcCriticalPoint(float X1onh, float NmaxOnN0);
    static float calcIndexCategory(float X1Onh);

    MathLogic();
    void handleSettings(float sampleHeight, float height, const float *array, int lenght);

    CalculedVals getCalculedVals() { return calculedVals; }

private:
    CalculedVals calculedVals;

    //Input
    float Lsh;
    float h;

    void handleImpulses(const float* array, int lenght);
};

#endif // MATHLOGIC_H

#include "math-logic.h"
#include "math-logic-func.cpp"

#include <QDebug>
#include <cmath>
#include "math-logic-func.h"

MathLogic::MathLogic() {
    //const value for graphics
    float* constList_X1Onh = new float[20];
    float* constList_NmaxOnN0 = new float[20];

    for (int i = 0; i < 20; ++i) {
        constList_X1Onh[i] = i * 0.05;
        constList_NmaxOnN0[i] =
                4.8 * std::pow(constList_X1Onh[i], 3) +
                14.0229 * std::pow(constList_X1Onh[i], 2) -
                1.5029 * constList_X1Onh[i] + 7.3129;
    }

    calculedVals.constList.constList_X1Onh = constList_X1Onh;
    calculedVals.constList.constList_NmaxOnN0 = constList_NmaxOnN0;
    calculedVals.constList.length = 20;
}



float MathLogic::findXFromMaxY(const float *Xs, const float *Ys, int length)
{
    const float maxY = math::maxValue<float>(Ys, length);

    int maxYOnIndex = 0;
    for (int i = 0; i < length; ++i) {
        if (maxY == Ys[i]) {
            maxYOnIndex = i;
        }
    }

    return Xs[maxYOnIndex];
}

float MathLogic::calcStrockRation(float Lsh, float h, float maxImpulse, float zeroImpulse)
{
    float LshOnh = Lsh / h;
    float maxImpulseOnZeroImpulse = maxImpulse / zeroImpulse;
    float calcValue =
            (float(4.8)*std::pow(LshOnh, 3) +
            float(14.0229)*pow(LshOnh, 2) -
            float(1.5029) * LshOnh +
            float(7.3129)) / maxImpulseOnZeroImpulse;
    return calcValue;
}

CriticalPoint MathLogic::calcCriticalPoint(float X1onh, float NmaxOnN0)
{
    float X1Onh_point = X1onh * 20 + 1;

    const CriticalPoint criticalPoint = {X1Onh_point, NmaxOnN0};
    return criticalPoint;
}

float MathLogic::calcIndexCategory(float X1Onh) {
    float calcVal =
            float(4.8) * std::pow(X1Onh, 3) +
            float(14.0229) * std::pow(X1Onh, 2) -
            float(1.5029) * X1Onh +
            float(7.3129);
    return calcVal;
}

void MathLogic::handleSettings(float Lsh, float h, const float *impulses, int measurementsLenght) {
    this->Lsh = Lsh;
    this->h = h;
    handleImpulses(impulses, measurementsLenght);
}

void MathLogic::handleImpulses(const float *impulses, int length)
{
    calculedVals.calcList = {new float[length], new float[length], length};
    float *calcImpulses = calculedVals.calcList.impulses;
    float *calcDepths = calculedVals.calcList.depths;
    float step = this->Lsh / float(length - 1);
    for (int i = 0; i < length; ++i) {
        calcImpulses[i] = impulses[i];
        if (i == 0){
            calcDepths[0] = 0;
            continue;
        }
            calcDepths[i] = step + calcDepths[i - 1];
    }

    calculedVals.N0 = impulses[0];
    calculedVals.Nmax = math::maxValue<float>(impulses, length);
    calculedVals.NmaxOnN0 = float(calculedVals.Nmax / calculedVals.N0);

    float X1 = this->findXFromMaxY(calcImpulses, calcDepths, length);;//DepthFromMaxImpulses
    calculedVals.X1Onh = X1 / h;

    float indexCategory = calcIndexCategory(calculedVals.X1Onh);
    calculedVals.category = calculedVals.NmaxOnN0 > indexCategory ? "ОПАСНО" : "НЕОПАСНО";

    calculedVals.strockRation = calcStrockRation(this->Lsh, this->h, calculedVals.Nmax, calculedVals.N0);

    calculedVals.criticalPoint = MathLogic::calcCriticalPoint(calculedVals.X1Onh, calculedVals.NmaxOnN0);
}



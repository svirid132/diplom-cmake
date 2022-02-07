#include <QtTest>
#include <QCoreApplication>
#include <QDebug>

#include "math-logic.h"
#include "math-logic-func.h"

float round(float var)
{
    float value = (int)(var * 100 + .5);
    return (float)value / 100;
}

class MathLogicTest : public QObject
{
    Q_OBJECT

public:
    MathLogicTest() {};
    ~MathLogicTest() {};
    static bool isCompare(const float *ext_1, const float *ext_2, int length);

private:
    MathLogic* logic;

private slots:
    //static
    void initTestCase();
    void maxValue();
    void crititcalPoint();
    void calcStockRatio();
    void calcIndexCategory();

    //default method from class
    void handleImpulsesData();
    void handleFindMaxXFromY();
//    void cleanupTestCase();
};

bool MathLogicTest::isCompare(const float *ext_1, const float *ext_2, int length) {
    for (int i = 0; i < length; ++i) {
        if (round(ext_1[i]) != round(ext_2[i])) {
            qDebug() << i << ":" << round(ext_1[i]) << round(ext_2[i]);
            return false;
        }
    }
    return true;
};

void MathLogicTest::initTestCase()
{
    this->logic = new MathLogic();
    float impulses[20] = {588, 1700, 2500, 2000, 500, 160, 12, 0, 0, 0, 0, 230, 0, 0, 0, 0, 0, 0, 0};
    this->logic->handleSettings(2.5, 4.5, impulses, 20);
}

//void MathLogicTest::cleanupTestCase(){ }

void MathLogicTest::handleImpulsesData() {
    float impulses[20] = {588, 1700, 2500, 2000, 500, 160, 12, 0, 0, 0, 0, 230, 0, 0, 0, 0, 0, 0, 0};
    const CalculedVals checkRusults = logic->getCalculedVals();

    const float expectedDepths[20] = {0, 0.13, 0.26, 0.39, 0.53, 0.66, 0.79, 0.92, 1.05, 1.18, 1.32, 1.45, 1.58, 1.71, 1.84, 1.97, 2.11, 2.24, 2.37, 2.50};
    const CalculedLists lists = checkRusults.calcList;

    QCOMPARE(MathLogicTest::isCompare(lists.impulses, impulses, 20), true);
    QCOMPARE(MathLogicTest::isCompare(lists.depths, expectedDepths, 20), true);
    QCOMPARE(lists.length, 20);

    QCOMPARE(round(checkRusults.NmaxOnN0), round(4.251700));

    QCOMPARE(round(checkRusults.X1Onh), round(0.111111));
}

void MathLogicTest::handleFindMaxXFromY()
{
    const float Xs[3] = {1.3, 2.4, 6.5};
    const float Ys[3] = {5, 6.4, 2.5};
    QCOMPARE(MathLogic::findXFromMaxY(Xs, Ys, 3), float(2.4));
}

void MathLogicTest::maxValue()
{
    float array[6] = {2, 4, 10, 32, 12.432, 432423.54};
    float value = math::maxValue<float>(array, int(6));
    QCOMPARE(value, float(432423.54));
}

void MathLogicTest::calcStockRatio()
{
     float value = MathLogic::calcStrockRation(float(0.263157895), float(4.5), float(2500), float(588));
     QCOMPARE(round(value), round(float(1.710827716)));
}

void MathLogicTest::calcIndexCategory()
{
    float calcValue = MathLogic::calcIndexCategory(float(0.05848));
    QCOMPARE(round(calcValue), round(float(7.2739274)));
}

void MathLogicTest::crititcalPoint() {
    CriticalPoint point = MathLogic::calcCriticalPoint(float(0.05848), float(4.2517));
    QCOMPARE(round(point.X1Onh), round(float(2.169590643)));
    QCOMPARE(round(point.NmaxOnN0), round(float(4.25170068)));
}


QTEST_APPLESS_MAIN(MathLogicTest)//без GUI
#include "math-logic-test.moc"

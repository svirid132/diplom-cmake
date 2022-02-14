#include <QtTest>
#include <QCoreApplication>
#include <QDebug>
#include <QVector>
#include <API-var.h>
#include <math-logic.h>
#include "smath.h"

//int *const ptr - константные указатели
//const int *ptr - константные значения

class MathLogicTest : public QObject
{
    Q_OBJECT

public:

private:
    QVector<CountOverAmps> Nimp;
    float h = 4.5;
    float Lsh = 2.5;

private slots:
    void initTestCase();
    void handleCriticalPoint();
    void handleKoefZap();
    void handleGlub_Nimp();
};

void MathLogicTest::initTestCase()
{
    Nimp <<
            CountOverAmps({588, 1}) << CountOverAmps({1700, 1}) << CountOverAmps({2500, 1}) << CountOverAmps({2000, 1}) << CountOverAmps({500, 1}) <<
            CountOverAmps({160, 1}) << CountOverAmps({12, 1}) << CountOverAmps({0, 1}) << CountOverAmps({0, 1}) << CountOverAmps({0, 1}) <<
            CountOverAmps({0, 1}) << CountOverAmps({230, 1}) << CountOverAmps({0, 1}) << CountOverAmps({0, 1}) << CountOverAmps({0, 1}) <<
            CountOverAmps({0, 1}) << CountOverAmps({0, 1}) << CountOverAmps({0, 1}) << CountOverAmps({0, 1}) << CountOverAmps({0, 1});
}

void MathLogicTest::handleCriticalPoint(){

    QPointF point = MathLogic::getCriticalPoint(Nimp, Lsh, h);
    QPointF pointResult(0.05848, 4.25170068);
    QCOMPARE(
                smath::roundFloat(point.x()),
                smath::roundFloat(pointResult.x())
                );
    QCOMPARE(
                smath::roundFloat(point.y()),
                smath::roundFloat(pointResult.y())
                );
}

void MathLogicTest::handleKoefZap()
{
    float koefZap = MathLogic::getKoefZap(Nimp, Lsh, h);
    float result = 1.710827716;
    QCOMPARE(
                smath::roundFloat(koefZap),
                smath::roundFloat(result)
                );

}

void MathLogicTest::handleGlub_Nimp(){

    QVector<QPointF> Nimp_Glub = MathLogic::getGlub_Nimp(Nimp, Lsh);
    float glubResult[20] = {0, 0.13, 0.26, 0.39, 0.53, 0.66, 0.79, 0.92, 1.05, 1.18, 1.32, 1.45, 1.58, 1.71, 1.84, 1.97, 2.11, 2.24, 2.37, 2.50};
    int i = 0;
    for (QPointF point: Nimp_Glub) {
        QCOMPARE(
                    smath::roundFloat(point.x()),
                    glubResult[i]
                    );
        QCOMPARE(
                    point.y(),
                    Nimp[i].countAmps
                    );
        ++i;
    }
}

QTEST_APPLESS_MAIN(MathLogicTest)//без GUI
#include "math-logic-test.moc"

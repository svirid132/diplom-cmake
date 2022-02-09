#include <QtTest>
#include <QCoreApplication>
#include <QDebug>

#include "smath.h"

//int *const ptr - константные указатели
//const int *ptr - константные значения

class SmathTest : public QObject
{
    Q_OBJECT

public:
    static bool isCompare(const float *ext_1, const float *ext_2, int length);

private:

private slots:
    void roundFloat_data();
    void roundFloat();
    void minValue_data();
    void minValue();
    void maxValue_data();
    void maxValue();
};

void SmathTest::roundFloat_data()
{
    QTest::addColumn<float>("num");
    QTest::addColumn<float>("result");

    QTest::newRow("23.2323") << float(23.2323) <<float(23.23);
    QTest::newRow("23.2") << float(23.2) <<float(23.20);
    QTest::newRow("101.0101") << float(101.0101) <<float(101.01);
}

void SmathTest::roundFloat(){
    QFETCH(float, num);
    QFETCH(float, result);

//    QCOMPARE(smath::roundFloat(num), result);
}

void SmathTest::minValue_data()
{
    QTest::addColumn<QVector<float>>("nums");
    QTest::addColumn<int>("size");
    QTest::addColumn<float>("result");

    QVector<float> firstArr;
    QVector<float> secondArr;
    QVector<float> thridArr;
    firstArr << 1 << 2 << 3 << 4 << 5;
    secondArr << 2.3 << 1.2 << 3.6 << 4.8 << 5.9;
    thridArr << 2.34 << 1.26 << 3.61 << 4.84 << 5.93;
    QTest::newRow("1, 2, 3, 4, 5") << firstArr << 5 << float(1);
    QTest::newRow("2.3, 3.6, 4.8, 5.9, 1.2") << secondArr << 5 << float(1.2);
    QTest::newRow("2.34, 1.26, 3.61, 4.84, 5.93") << thridArr << 5 << float(1.26);
}

void SmathTest::minValue(){
    QFETCH(QVector<float>, nums);
    QFETCH(int, size);
    QFETCH(float, result);

    QCOMPARE(smath::minValue(nums.data(), size), float(result));
}

void SmathTest::maxValue_data()
{
    QTest::addColumn<QVector<float>>("nums");
    QTest::addColumn<int>("size");
    QTest::addColumn<float>("result");

    QVector<float> firstArr;
    QVector<float> secondArr;
    QVector<float> thridArr;
    firstArr << 1 << 2 << 3 << 4 << 5;
    secondArr << 2.3 << 1.2 << 3.6 << 4.8 << 5.9;
    thridArr << 2.34 << 1.26 << 3.61 << 4.84 << 5.93;
    QTest::newRow("1, 2, 3, 4, 5") << firstArr << 5 << float(5);
    QTest::newRow("2.3, 3.6, 4.8, 5.9, 1.2") << secondArr << 5 << float(5.9);
    QTest::newRow("2.34, 1.26, 3.61, 4.84, 5.93") << thridArr << 5 << float(5.93);
}

void SmathTest::maxValue(){
    QFETCH(QVector<float>, nums);
    QFETCH(int, size);
    QFETCH(float, result);

    QCOMPARE(smath::maxValue(nums.data(), size), result);
}

QTEST_APPLESS_MAIN(SmathTest)//без GUI
#include "smath-test.moc"

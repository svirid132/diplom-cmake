#include <QtTest>
#include <QCoreApplication>
#include <QDebug>
#include <rawfile.h>

//int *const ptr - константные указатели
//const int *ptr - константные значения

class RawFileTest : public QObject
{
    Q_OBJECT

public:

private:

private slots:
    void handleRawFile();
};

void RawFileTest::handleRawFile()
{
    QVector<CountOverAmps> countOverAmps = RawFile::handleFile(":/audio/triangle_mono_44100_16bit.raw");
    QCOMPARE(countOverAmps[0].countAmps, 5668);
    QCOMPARE(countOverAmps[1].countAmps, 5694);
}

QTEST_APPLESS_MAIN(RawFileTest)//без GUI
#include "raw-file-test.moc"

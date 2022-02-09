#ifndef RAWFILE_H
#define RAWFILE_H

#include "smath.h"
#include <QFile>
#include <QVector>
#include "API-var.h"

class RawFile {
public:
    //для mono, data - 2 байта(short), period - интервал(секунды)
    static QVector<CountOverAmps> handleFile(const QString& path, int period = 1) {
        QFile file(path);
        file.open(QIODevice::ReadOnly);
        QVector<CountOverAmps> results;

        int hz = 44100;
        int depth = 2;
        int countBytePeriod = hz * depth;
        int countAmpsOnPeriod = countBytePeriod / depth;
        int numPeriod = 0;

        while(!file.atEnd()) {
            QByteArray arrByte = file.read(countBytePeriod);
            if (countBytePeriod == arrByte.size()) {
                ++numPeriod;
                handlePeriod(results, arrByte, countAmpsOnPeriod, numPeriod);
            }
        }
        return results;
    }
protected:
    static void handlePeriod(QVector<CountOverAmps>& list, const QByteArray& arrByte, int countAmpsOnPeriod, int numPeriod) {
        short arr[countAmpsOnPeriod];
        for (int i = 0, a = 0; i < arrByte.size(); i += 2, ++a) {
            Amp amp;
            amp.symbols[0] = arrByte[i];
            amp.symbols[1] = arrByte[i + 1];
            arr[a] = amp.number;
        }
        CountOverAmps countOverAmps = {0, numPeriod};
        short maxAmp = smath::maxValue<short>(arr, countAmpsOnPeriod);
        short borderAmp = maxAmp * 0.75;
        for (int i = 0; i < countAmpsOnPeriod; ++i) {
            if (borderAmp <= arr[i]) {
                ++countOverAmps.countAmps;
            }
        }
        list.append(countOverAmps);
    }
private:
    union Amp {
        char symbols[2];
        short number;
    };
};
#endif // RAWFILE_H

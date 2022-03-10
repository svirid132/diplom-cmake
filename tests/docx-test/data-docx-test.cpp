//
// Created by sviri on 10.03.2022.
//

#include "data-docx-test.h"
#include <smath.h>
#include <QtCore/QPointF>
#include "QtCore/QList"

DocData getDocData() {
    DocData docData;
    docData.N0 = 20;
    docData.Nmax = 1999;
    docData.Nmax_N0 = smath::roundFloat(float(docData.Nmax) / float(docData.N0));//99.95
    docData.Xm = 123.3;
    docData.h = 4.5;
    docData.Xm_h = smath::roundFloat(float(docData.Xm) / float(docData.h));//27.4
    docData.category = "НЕОПАСНО";
    docData.X = 21;
    docData.Y = 22;
    docData.Z = -23.23;
    docData.posDescWritter = "Главный геотехник ЗФ ПАО «ГМК «Норильский никель» – директор Центра геодинамической безопасности";
    docData.nameWritter = "В.П. Марысюк";
    docData.product = "РВ-2";
    docData.dateProduct = "19.01.2022";
    docData.posDescMain = "И.о. главного инженера Центра геодинамической безопасности ЗФ ПАО «ГМК «Норильский никель» (далее – ЦГБ, ЗФ соответственно) Сергунин М.П.";
    docData.posDescMembOne = "1. Начальник подземного участка прогноза и предотвращения горных ударов рудника «Скалистый» ЦГБ ЗФ Шаховцев В.Е.";
    docData.posDescMembTwo = "2. И.о. начальника отдела геотехнического сопровождения горных работ (далее – ОГТСГР) ЦГБ ЗФ Сазнов В.В.";
    docData.rudnik = "Скалистый";
    docData.koefZap = 1.84;
    docData.nameMain = "М.П. Сергунин";
    docData.nameMembOne = "В.Е. Шаховцев";
    docData.nameMembTwo = "В.В. Сазнов";

    return docData;
}

QList<QPointF> getGlub_Nimp() {
    QList<QPointF> Glub_Nimp = { QPointF(0, 588), QPointF(0.131579, 1700), QPointF(0.263158, 2500), QPointF(0.394737, 2000), QPointF(0.526316, 500),
            QPointF(0.657895, 160), QPointF(0.789474, 12), QPointF(0.921053, 0), QPointF(1.05263, 0), QPointF(1.18421, 0), QPointF(1.31579, 0),
            QPointF(1.44737, 230), QPointF(1.57895, 0), QPointF(1.71053, 0), QPointF(1.84211, 0), QPointF(1.97368, 0), QPointF(2.10526, 0),
            QPointF(2.23684, 0), QPointF(2.36842, 0), QPointF(2.5, 0)
    };
    return Glub_Nimp;
};

QPointF getCriticalPoint() {
    return QPointF(0.0584795,4.2517);
}


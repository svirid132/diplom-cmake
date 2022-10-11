//
// Created by sviri on 11.03.2022.
//

#include <QtCore/QDebug>
#include <QtCore/QSettings>
#include "InitDialogCommission.h"
#include "../global-var.h"

std::function<DataCommission(const DialogParam& param, const DataCommission& data, bool& ok)> initDialogCommission(MainWindow& window){
    const QString organization = "settings";
    QSettings settings(organization);
    DataCommission loadData;
    QVariant varData = settings.value("nameWritter");
    if (!varData.isNull()) {
        loadData.nameWritter = varData.toString();
        varData = settings.value("posDescWritter");
        loadData.posDescWritter = varData.toString();
        varData = settings.value("nameMain");
        loadData.nameMain = varData.toString();
        varData = settings.value("posDescMain");
        loadData.posDescMain = varData.toString();
        varData = settings.value("nameMembOne");
        loadData.nameMembOne = varData.toString();
        varData = settings.value("posDescMembOne");
        loadData.posDescMembOne = varData.toString();
        varData = settings.value("nameMembTwo");
        loadData.nameMembTwo = varData.toString();
        varData = settings.value("posDescMembTwo");
        loadData.posDescMembTwo = varData.toString();

        window.setDataCommission(loadData);
    }
    return [=](const DialogParam& param, const DataCommission& data, bool& ok) {
        DialogCommission dialog(param.mainWidget);
        dialog.setDataCommission(data);
        const int width = dialog.width();
        const int height = dialog.height();
        dialog.setGeometry(
                WIDTH_SCREEN / 2 - width / 2,
                HEIGHT_SCREEN / 2 - height / 2,
                width,
                height);
        dialog.saveGeometry();
        dialog.show();
        dialog.exec();
        dialog.result() == 1 ? ok = true : ok = false;

        DataCommission dataComp = dialog.getDataCommission();
        QVariant varData;
        varData.setValue(dataComp);
        if (ok == true) {
            QSettings settings(organization);
            settings.setValue("nameWritter", dataComp.nameWritter);
            settings.setValue("posDescWritter", dataComp.posDescWritter);
            settings.setValue("nameMain", dataComp.nameMain);
            settings.setValue("posDescMain", dataComp.posDescMain);
            settings.setValue("nameMembOne", dataComp.nameMembOne);
            settings.setValue("posDescMembOne", dataComp.posDescMembOne);
            settings.setValue("nameMembTwo", dataComp.nameMembTwo);
            settings.setValue("posDescMembTwo", dataComp.posDescMembTwo);
        }

        return dataComp;
    };
}

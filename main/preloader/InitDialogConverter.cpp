//
// Created by Пользователь on 16.03.2022.
//

#include <DialogConverter.h>
#include <QtCore/QFileInfo>
#include "InitDialogConverter.h"
#include "../API/XMLtoDOCX.h"
#include "../error/error.h"

DocCommission DataCommissionToDocCommission(const DataCommission& dataCommission) {
    DocCommission docCom;
    docCom.posDescWritter = dataCommission.posDescWritter;
    docCom.posDescMain = dataCommission.posDescMain;
    docCom.posDescMembOne = dataCommission.posDescMembOne;
    docCom.posDescMembTwo = dataCommission.posDescMembTwo;
    docCom.nameWritter = dataCommission.nameWritter;
    docCom.nameMain = dataCommission.nameMain;
    docCom.nameMembOne = dataCommission.nameMembOne;
    docCom.nameMembTwo = dataCommission.nameMembTwo;

    return docCom;
}

std::function<QString(const DialogParam& param, const QString& docxPath, bool& ok)> initDialogConverter(MainWindow& window, const QString& dirDocx ) {

    window.setDocxPath(dirDocx);

    return [=, &window](const DialogParam& param, const QString& docxPath, bool& ok) {
        DialogConverter dialog(param.mainWidget);
        QFileInfo dirInfoDocx(docxPath);
        dialog.setDocxPath(dirInfoDocx.absoluteFilePath());
        dialog.exec();
        if (dialog.result() == QDialog::Accepted) {
            try {
                QString docxPath = dialog.getDocxPath();
                QString xmlFilePath = dialog.getXmlFilePath();

                XMLtoDOCX xmlToDocx;
                xmlToDocx.setFilePathXML(xmlFilePath);
                xmlToDocx.setPathDocx(docxPath);
                DataCommission dataCom = window.getDataCommission();
                DocCommission docCommission = DataCommissionToDocCommission(dataCom);
                if (!xmlToDocx.convert(docCommission)) throw Error("Не удалось переконвертировать в docx файл!");
                QString docxFilePath = xmlToDocx.getDocxFilePath();
                QFileInfo info(docxFilePath);
                if(info.exists()) {
                    int result = window.dialogQuestion(
                            QString("docx файл по пути %1 уже существует!").arg(docxFilePath),
                            "Заменить его?"
                            );
                    if (result != QDialog::Accepted) {
                        return QString();
                    }
                }
                xmlToDocx.saveDocx();
                ok = true;
                window.viewSuccess(QString("docx файл успешно создан. Полный путь %1").arg(docxFilePath));
                return docxPath;
            } catch (const Error& error) {
                window.viewError(error.what());
            }
        }

        return QString();
    };
}
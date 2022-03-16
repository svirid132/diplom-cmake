//
// Created by Пользователь on 15.03.2022.
//

#ifndef DIPLOM_CMAKE_DIALOGCONVERTER_H
#define DIPLOM_CMAKE_DIALOGCONVERTER_H


#include <QtWidgets/QDialog>
#include <QtWidgets/QLineEdit>

class DialogConverter : public QDialog {
    Q_OBJECT
public:
    explicit DialogConverter(QWidget *parent = nullptr);

    void setDocxPath(const QString& docxPath);

    QString getXmlFilePath();
    QString getDocxPath();

public slots:
    void acceptSlot();
    void xmlDiloag();
    void docxDialog();

private:
    QString xmlFilePath;
    QString docxPath;

    QLineEdit* lineXml;
    QLineEdit* lineDocx;

    QPushButton* btnXML;
    QPushButton* btnDocx;
};


#endif //DIPLOM_CMAKE_DIALOGCONVERTER_H

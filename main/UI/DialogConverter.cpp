//
// Created by Пользователь on 15.03.2022.
//

#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFileDialog>
#include "DialogConverter.h"
#include "DialogCommission.h"

DialogConverter::DialogConverter(QWidget *parent) :
    QDialog(parent),
    lineXml(new QLineEdit),
    lineDocx(new QLineEdit)
{

    QGridLayout* gridLayout = new QGridLayout();

    gridLayout->addWidget(new QLabel("Путь к XML файлу"), 0, 0);
    gridLayout->addWidget(new QLabel("Путь к docx папке"), 1, 0);

    lineXml->setFixedWidth(300);
    lineXml->setDisabled(true);
    lineDocx->setEnabled(false);
    gridLayout->addWidget(lineXml, 0, 1);
    gridLayout->addWidget(lineDocx, 1, 1);

    btnXML = new QPushButton("...");
    btnDocx = new QPushButton("...");
    connect(btnXML, &QPushButton::clicked, this, &DialogConverter::xmlDiloag);
    connect(btnDocx, &QPushButton::clicked, this, &DialogConverter::docxDialog);
    btnXML->setFixedWidth(30);
    btnDocx->setFixedWidth(30);
    gridLayout->addWidget(btnXML, 0, 2);
    gridLayout->addWidget(btnDocx, 1, 2);

    //button
    QDialogButtonBox* buttonBox = new QDialogButtonBox(Qt::Horizontal);
    buttonBox->addButton(new QPushButton("Ok"), QDialogButtonBox::AcceptRole);
    buttonBox->addButton(new QPushButton("Отмена"), QDialogButtonBox::RejectRole);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &DialogConverter::acceptSlot);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &DialogConverter::reject);

    //Vertical layout
    QVBoxLayout* verticalLayout = new QVBoxLayout;
    verticalLayout->addLayout(gridLayout);
    verticalLayout->addWidget(buttonBox);

    this->setLayout(verticalLayout);
    this->setWindowTitle("Конвертировать Xml в Docx");
}

void DialogConverter::setDocxPath(const QString &docxPath) {
    this->docxPath = docxPath;
    lineDocx->setText(docxPath);
}

void DialogConverter::docxDialog() {
    btnDocx->setStyleSheet("");
    QString pathDir = QFileDialog::getExistingDirectory(this, "Папка для сохранения Docx", docxPath, QFileDialog::ShowDirsOnly);
    if (pathDir != "") {
        lineDocx->setText(pathDir);
        this->docxPath = pathDir;
    }
}

void DialogConverter::xmlDiloag() {
    btnXML->setStyleSheet("");
    QString pathFile = QFileDialog::getOpenFileName(this, "Выбор XML файла", docxPath, "Файл (*.xml)");
    if (pathFile != "") {
        lineXml->setText(pathFile);
        this->xmlFilePath = pathFile;
    }
}

QString DialogConverter::getXmlFilePath() {
    return xmlFilePath;
}

QString DialogConverter::getDocxPath() {
    return docxPath;
}

void DialogConverter::acceptSlot() {
    QString styleSheet = "background-color: red;";
    QFileInfo infoXml = QFileInfo(xmlFilePath);
    QFileInfo infoDocx = QFileInfo(docxPath);
    if(!infoXml.exists()) {
        btnXML->setStyleSheet(styleSheet);
        return;
    }
    if(!infoDocx.exists()) {
        btnDocx->setStyleSheet(styleSheet);
        return;
    }

    this->accept();
}

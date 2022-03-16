#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "widgetmain.h"

#include <QDebug>
#include <QErrorMessage>
#include <QMessageBox>
#include "../global-var.h"
#include "DialogCommission.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::viewError(const QString &str) {
    QMessageBox messageBox;
    int width = messageBox.size().width();
    int height = messageBox.size().height();
    messageBox.setText(str);
    messageBox.setWindowTitle("Ошибка");
    messageBox.setIcon(QMessageBox::Critical);
    messageBox.setGeometry(
            WIDTH_SCREEN / 2 - width / 2,
            HEIGHT_SCREEN / 2 - height / 2,
            width,
            height);
    messageBox.exec();
}

void MainWindow::viewSuccess(const QString &str) {
    QMessageBox messageBox;
    int width = messageBox.size().width();
    int height = messageBox.size().height();
    messageBox.setText(str);
    messageBox.setWindowTitle("Успех");
    messageBox.setIcon(QMessageBox::Information);
    messageBox.setGeometry(
            WIDTH_SCREEN / 2 - width / 2,
            HEIGHT_SCREEN / 2 - height / 2,
            width,
            height);
    messageBox.exec();
}

void MainWindow::setCentralWidget(QWidget *widget) {
    widget->setFixedSize(800, 450);
    QMainWindow::setCentralWidget(widget);
}

void MainWindow::setDataCommission(const DataCommission &data) {
    dataCommission = data;
}

bool MainWindow::isDataCommission() {
    bool isData = (dataCommission.nameWritter != "-1");
    return isData;
}

DataCommission MainWindow::getDataCommission() {
    return dataCommission;
}

void MainWindow::dialogCommission() {
    DialogParam param;
    param.mainWidget = this;
    bool ok;
    DataCommission newData = openCommissionDialog(param, dataCommission, ok);
    if (ok) {
        dataCommission = newData;
    }
}

void MainWindow::dialogConveter() {
    DialogParam param;
    param.mainWidget = this;
    bool ok;
    QString docxPath = openConverterDialog(param, this->docxPath, ok);
    if (ok) {
        this->docxPath = docxPath;
    }
}

void
MainWindow::setDialogCommission(
        std::function<DataCommission(const DialogParam &, const DataCommission &, bool &)> dialog) {
    openCommissionDialog = dialog;
}

bool MainWindow::dialogQuestion(const QString &propblem, const QString &question) {
    QMessageBox messageBox;
    messageBox.setInformativeText(question);
    messageBox.setText(propblem);
    int width = messageBox.size().width();
    int height = messageBox.size().height();
    messageBox.setWindowTitle("Вопрос");
    messageBox.addButton("Да", QMessageBox::AcceptRole);
    messageBox.addButton("Нет", QMessageBox::RejectRole);
    messageBox.setIcon(QMessageBox::Information);
    messageBox.setGeometry(
            WIDTH_SCREEN / 2 - width / 2,
            HEIGHT_SCREEN / 2 - height / 2,
            width,
            height);
    messageBox.exec();
    int result = messageBox.result();
    bool isAccept = (result == QMessageBox::AcceptRole);
    return isAccept;
}

void MainWindow::setDocxPath(const QString &path) {
    this->docxPath = path;
}

void MainWindow::setDialogConverter(
        std::function<QString(const DialogParam &param, const QString &docxPath, bool &ok)> dialog) {
    this->openConverterDialog = dialog;
}


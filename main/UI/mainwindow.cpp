#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "widgetmain.h"

#include <QDebug>
#include <QErrorMessage>
#include <QMessageBox>
#include "../global-var.h"
#include "DialogCommission.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::viewError(const QString& str) {
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

void MainWindow::viewSuccess(const QString& str) {
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

void MainWindow::commissionDialog() {
    DialogCommission dialog(this);
    dialog.show();

    dialog.exec();

    int result = dialog.result();//1 - ок; 0 - cancel
    if (result == 1) {

    } else {

    }
}

void MainWindow::setCentralWidget(QWidget *widget)
{
    widget->setFixedSize(800, 450);
    QMainWindow::setCentralWidget(widget);
}


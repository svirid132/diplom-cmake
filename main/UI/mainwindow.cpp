#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "widgetchart.h"

#include <QDebug>

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

void MainWindow::setCentralWidget(QWidget *widget)
{
    widget->setFixedSize(800, 450);
    QMainWindow::setCentralWidget(widget);
}


#include "mainwindow.h"
#include <QVBoxLayout>
#include <QtWidgets/QScrollArea>
#include "PushButton.h"
#include "LineEdit.h"
#include <QDebug>
#include <QtCore/QDir>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include "SettingsUI.h"

QString getStyles(const QString& dirPath) {
    QDir dir(dirPath);
    if(!dir.exists()) return "";
    qDebug() << "dir exists";

    QString final = "";
    QFileInfoList infoList = dir.entryInfoList(QStringList({"*.qss"}), QDir::Files);
    for (auto fileInfo: infoList) {
        qDebug() << "file";
        QFile file(fileInfo.absoluteFilePath());
        if(file.open(QIODevice::ReadOnly)) {
            QString path = QString::fromUtf8(file.readAll());
            final += path;
        }
    }
    return final;
}

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent) {

    QString data = getStyles(":/dir-styles");
    this->setStyleSheet(data);

    PushButton *pushButton = new PushButton(this);
//    pushButton->setStyleSheet("QPushButton { \n"
//                              "\tpadding: 3px 0px;\n"
//                              "\tbackground-color: white;\n"
//                              "\tmax-height: 30px;\n"
//                              "\tmin-height: 30px;\n"
//                              "\tborder: 2px solid #C4C4C4;\n"
//                              "\tborder-radius: 15px;\n"
//                              "\ttext-align: center;}\n"
//                              "QPushButton:hover, QPushButton:focus {\n"
//                              "\tborder-color: #34D5EB;"
//                              "}");

    QSpinBox* spinBox = new QSpinBox(this);
    SettingsUI::spinBox(spinBox);
    spinBox->move(500, 500);

    QComboBox* comboBox = new QComboBox(this);
    comboBox->move(400, 200);
    comboBox->addItem("123");
    comboBox->addItem("321");
    comboBox->addItem("567");

    QLineEdit* lineEdit = new QLineEdit(this);
    lineEdit->setText("123");
    PushButton* button = new PushButton(this);
    button->setText("321");
    button->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
    QVBoxLayout* vBox = new QVBoxLayout();
    vBox->setSizeConstraint(QLayout::SetFixedSize);
    vBox->addWidget(lineEdit);
    vBox->addWidget(button, 0, Qt::AlignHCenter);
    QGroupBox* grBox = new QGroupBox(this);
    grBox->setTitle("Выбор файла");
//    grBox->setFixedHeight(100);
    grBox->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    grBox->setFixedWidth(200);
    grBox->setLayout(vBox);
    grBox->move(500, 400);
    grBox->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
    grBox->setEnabled(false);

    pushButton->setText("Здес");
    QPixmap pixmap = QIcon(":/error.svg").pixmap(QSize(25, 25));
//    pushButton->error();
    pushButton->move(25, 25);

    QVBoxLayout *boxLayout = new QVBoxLayout();
//    for (int i = 0; i < 20; ++i) {
//        PushButton *button = new PushButton("Здесь очень длинный еще текст!");
////        button->error();
//        button->setStyleSheet("QPushButton { \n"
//                              "\tpadding: 3px 0px;\n"
//                              "\tbackground-color: white;\n"
//                              "\tmax-height: 20px;\n"
//                              "\tmin-height: 20px;\n"
//                              "\tborder: 2px solid #C4C4C4;\n"
//                              "\tborder-radius: 15px;\n"
//                              "\ttext-align: center;}\n"
//                              "QPushButton:hover, QPushButton:focus {\n"
//                              "\tborder-color: #34D5EB;"
//                              "}");
//
//        boxLayout->addWidget(button);
//    }
    for (int i = 0; i < 20; ++i) {
        LineEdit* lineEdit = new LineEdit("Зд");
//        button->error();
//        lineEdit->setStyleSheet("QPushButton { \n"
//                              "\tpadding: 3px 0px;\n"
//                              "\tbackground-color: white;\n"
//                              "\tmax-height: 20px;\n"
//                              "\tmin-height: 20px;\n"
//                              "\tborder: 2px solid #C4C4C4;\n"
//                              "\tborder-radius: 15px;\n"
//                              "\ttext-align: center;}\n"
//                              "QPushButton:hover, QPushButton:focus {\n"
//                              "\tborder-color: #34D5EB;"
//                              "}");

        boxLayout->addWidget(lineEdit);
    }
    QWidget *widget = new QWidget();
//    widget->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Minimum);
//    widget->setStyleSheet("QWidget {padding: 10px;}");
//    boxLayout->setSpacing(20);
//    widget->setFixedWidth(300);
    widget->setLayout(boxLayout);

    QScrollArea *scroll = new QScrollArea();
    scroll->setWidgetResizable(true);
    scroll->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

//    scroll->setStyleSheet("QScrollArea { border: none; background-color: transparent; }"
//                          "QScrollBar:vertical {  border: none; background-color: transparent; width: 5px;}"
//                          "QScrollBar::horizontal { border: none; background-color: transparent; height: 5px; }"
//                          "QScrollBar::add-line, QScrollBar::sub-line { border: none; width: 0px; height: 0px; }"
//                          "QScrollBar::add-page, QScrollBar::sub-page { background-color: transparent; }"
//                          "QScrollBar::handle { background-color: #C4C4C4; border-radius: 2px; }"
//                          );
    scroll->setParent(this);

    scroll->setFixedWidth(200);
    scroll->setFixedHeight(300);
    scroll->setWidget(widget);
    this->setCentralWidget(scroll);
//    this->setCentralWidget(grBox);
    scroll->move(100, 100);
}

MainWindow::~MainWindow() {
}

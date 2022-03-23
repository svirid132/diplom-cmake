#include "mainwindow.h"
#include <QVBoxLayout>
#include <QtWidgets/QScrollArea>
#include "PushButton.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent) {


    PushButton* pushButton = new PushButton(this);
    pushButton->setStyleSheet("QPushButton { \n"
                              "\tpadding: 3px 0px;\n"
                              "\tbackground-color: white;\n"
                              "\tmax-height: 30px;\n"
                              "\tmin-height: 30px;\n"
                              "\tborder: 2px solid #C4C4C4;\n"
                              "\tborder-radius: 15px;\n"
                              "\ttext-align: center;}\n"
                              "QPushButton:hover, QPushButton:focus {\n"
                              "\tborder-color: #34D5EB;"
                              "}");


    pushButton->setText("Здесь очень длинный еще текст!");
    QPixmap pixmap = QIcon(":/error.svg").pixmap(QSize(25,25));
//    pushButton->error();
    pushButton->move(25, 25);

    QVBoxLayout* boxLayout = new QVBoxLayout();
    for (int i = 0; i < 20; ++i) {
        PushButton* button = new PushButton("Здесь очень длинный еще текст!");
//        button->error();
        button->setStyleSheet("QPushButton { \n"
                                  "\tpadding: 3px 0px;\n"
                                  "\tbackground-color: white;\n"
                                  "\tmax-height: 20px;\n"
                                  "\tmin-height: 20px;\n"
                                  "\tborder: 2px solid #C4C4C4;\n"
                                  "\tborder-radius: 15px;\n"
                                  "\ttext-align: center;}\n"
                                  "QPushButton:hover, QPushButton:focus {\n"
                                  "\tborder-color: #34D5EB;"
                                  "}");

        boxLayout->addWidget(button);

        qDebug() << "button.size(): " << button->size();
    }
    QWidget* widget = new QWidget();
//    widget->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Minimum);
//    widget->setStyleSheet("QWidget {padding: 10px;}");
//    boxLayout->setSpacing(20);
//    widget->setFixedWidth(300);
    widget->setLayout(boxLayout);

    QScrollArea* scroll = new QScrollArea(this);
    scroll->setWidgetResizable(true);
    scroll->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
//    scroll->setStyleSheet(" "
//                          "QScrollArea {"
////                          "border: none;"
//                          "}"
//                          ""
//                          "QScrollBar { \n"
//                          "background:  none;"
//                          "border: 0px;"
//                          "width: 5px;"
//                              "}"
//                              ""
//                              "QScrollBar::handle:vertical {"
//                          "background-color: #C4C4C4;"
//                          "border-radius: 3px;"
//                              "}");
    scroll->setFixedWidth(200);
    scroll->setFixedHeight(300);
    scroll->setWidget(widget);
    scroll->move(100, 100);
}

MainWindow::~MainWindow() {
}

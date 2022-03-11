//
// Created by Пользователь on 10.03.2022.
//

#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QScrollArea>
#include "DialogCommission.h"
#include <QDebug>

DialogCommission::DialogCommission(QWidget *parent) : QDialog(parent)
{
    QGridLayout* gridLayout = new QGridLayout();
    gridLayout->setColumnStretch(1, 1);
    gridLayout->setColumnStretch(2, 3);

//    gridLayout->addWidget(new QLabel("Hellow world"), 0, 0);
    gridLayout->addWidget(new QLabel("Имя"), 0, 1);
    gridLayout->addWidget(new QLabel("Должность"), 0, 2);

    QTextEdit* writterText = new QTextEdit;
    QLineEdit* writterName = new QLineEdit;
    writterName->setObjectName(nameWritter);
    writterText->setObjectName(posDescWritter);
    gridLayout->addWidget(new QLabel("Подписант"), 1, 0);
    gridLayout->addWidget(writterName, 1, 1);
    gridLayout->addWidget(writterText, 1, 2);
    inputWidget.append(writterText);
    inputWidget.append(writterName);

    QTextEdit* mainerText = new QTextEdit;
    QLineEdit* mainerName = new QLineEdit;
    mainerName->setObjectName(nameMain);
    mainerText->setObjectName(posDescMain);
    gridLayout->addWidget(new QLabel("Предсидатель\nкоммисии"), 2, 0);
    gridLayout->addWidget(mainerName, 2, 1);
    gridLayout->addWidget(mainerText, 2, 2);
    inputWidget.append(mainerText);
    inputWidget.append(mainerName);

    QTextEdit* membOneText = new QTextEdit;
    QLineEdit* membOneName = new QLineEdit;
    membOneName->setObjectName(nameMembOne);
    membOneText->setObjectName(posDescMembOne);
    gridLayout->addWidget(new QLabel("Член\nкомиссии (1)"), 3, 0);
    gridLayout->addWidget(membOneName, 3, 1);
    gridLayout->addWidget(membOneText, 3, 2);
    inputWidget.append(membOneText);
    inputWidget.append(membOneName);

    QTextEdit* membTwoText = new QTextEdit;
    QLineEdit* membTwoName = new QLineEdit;
    membTwoName->setObjectName(nameMembTwo);
    membTwoText->setObjectName(posDescMembTwo);
    gridLayout->addWidget(new QLabel("Член\nкомиссии (2)"), 4, 0);
    gridLayout->addWidget(membTwoName, 4, 1);
    gridLayout->addWidget(membTwoText, 4, 2);
    inputWidget.append(membTwoText);
    inputWidget.append(membTwoName);

    QScrollArea* scrollArea = new QScrollArea;
    scrollArea->setLayout(gridLayout);

    //button
    QDialogButtonBox* buttonBox = new QDialogButtonBox(Qt::Horizontal);
    buttonBox->addButton(new QPushButton("Ok"), QDialogButtonBox::AcceptRole);
    buttonBox->addButton(new QPushButton("Отмена"), QDialogButtonBox::RejectRole);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &DialogCommission::acceptSlot);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    //scrollArea + button
    QVBoxLayout* verticalLayout = new QVBoxLayout;
    verticalLayout->addWidget(scrollArea);
    verticalLayout->addWidget(buttonBox);

    adjustInputWidget();

    this->setLayout(verticalLayout);
    this->setFixedSize(800, 450);
    this->setWindowTitle("Состав коммиссии");
}

void DialogCommission::acceptSlot() {
    bool isAccepted = true;
    for (QWidget* widget: inputWidget) {
        bool isInnerAccepted = true;
        QTextEdit* textEdit = qobject_cast<QTextEdit*>(widget);
        if (textEdit) {
            QString text = textEdit->toPlainText();
            if (text == "") isInnerAccepted = false;
        }

        QLineEdit* lineEdit = qobject_cast<QLineEdit*>(widget);
        if (lineEdit) {
            QString text = lineEdit->text();
            if (text == "") isInnerAccepted = false;
        }

        if(!isInnerAccepted) {
            isAccepted = false;
            QString style = "background-color: red;";
            widget->setStyleSheet(style);
        }
    }
    if (!isAccepted) return;
    this->accept();
}

void DialogCommission::setDataCommission(const DataCommission& data) {
    dataCommission = data;

    for (QWidget* widget: inputWidget) {
        QTextEdit* textEdit = qobject_cast<QTextEdit*>(widget);
        if (textEdit) {
            QString objectName = widget->objectName();
            if (objectName == posDescWritter) {
                textEdit->setText(dataCommission.posDescWritter);
            } else if (objectName == posDescMain) {
                textEdit->setText(dataCommission.posDescMain);
            } else if(objectName == posDescMembOne) {
                textEdit->setText(dataCommission.posDescMembOne);
            } else if(objectName == posDescMembTwo){
                textEdit->setText(dataCommission.posDescMembTwo);
            }
        }

        QLineEdit* lineEdit = qobject_cast<QLineEdit*>(widget);
        if (lineEdit) {
            QString objectName = widget->objectName();
            if (objectName == nameWritter && dataCommission.nameWritter != "-1") {
                lineEdit->setText(dataCommission.nameWritter);
            } else if (objectName == nameMain) {
                lineEdit->setText(dataCommission.nameMain);
            } else if(objectName == nameMembOne) {
                lineEdit->setText(dataCommission.nameMembOne);
            } else if(objectName == nameMembTwo){
                lineEdit->setText(dataCommission.nameMembTwo);
            }
        }
    }

}

DataCommission DialogCommission::getDataCommission() {
    return dataCommission;
}

void DialogCommission::adjustInputWidget() {
    const QString style = "background-color: white";

    for (QWidget* widget: inputWidget) {
        QTextEdit* textEdit = qobject_cast<QTextEdit*>(widget);
        if (textEdit) {
            connect(textEdit, &QTextEdit::textChanged, [=]() {
                textEdit->setStyleSheet(style);
                QString text = textEdit->toPlainText();
                QString objectName = widget->objectName();
                if (objectName == posDescWritter) {
                    dataCommission.posDescWritter = text;
                } else if (objectName == posDescMain) {
                    dataCommission.posDescMain = text;
                } else if(objectName == posDescMembOne) {
                    dataCommission.posDescMembOne = text;
                } else if(objectName == posDescMembTwo){
                    dataCommission.posDescMembTwo = text;
                }
            });
        }

        QLineEdit* lineEdit = qobject_cast<QLineEdit*>(widget);
        if (lineEdit) {
            connect(lineEdit, &QLineEdit::textChanged, [=]() {
                lineEdit->setStyleSheet(style);
                QString text = lineEdit->text();
                QString objectName = widget->objectName();
                if (objectName == nameWritter) {
                    dataCommission.nameWritter = text;
                } else if (objectName == nameMain) {
                    dataCommission.nameMain = text;
                } else if(objectName == nameMembOne) {
                    dataCommission.nameMembOne = text;
                } else if(objectName == nameMembTwo){
                    dataCommission.nameMembTwo = text;
                }
            });
        }
    }
}

//
// Created by Пользователь on 10.03.2022.
//

#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QPushButton>
#include "DialogCommission.h"

DialogCommission::DialogCommission(QWidget *parent) : QDialog(parent)
{
    QGridLayout* gridLayout = new QGridLayout();
    gridLayout->addWidget(new QLabel("Hellow world"), 0, 0);

    QDialogButtonBox* buttonBox = new QDialogButtonBox(Qt::Horizontal);
    buttonBox->addButton(new QPushButton("Ok"), QDialogButtonBox::AcceptRole);
    buttonBox->addButton(new QPushButton("Отмена"), QDialogButtonBox::RejectRole);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    gridLayout->addWidget(buttonBox, 1, 0);

    this->setLayout(gridLayout);
}

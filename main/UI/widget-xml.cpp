#include "widget-xml.h"

#include <QComboBox>
#include <QDate>
#include <QDateEdit>
#include <QDebug>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QStringListModel>

WidgetXML::WidgetXML(QWidget *parent) : QWidget(parent)
{
    QFormLayout* formLayout = new QFormLayout();

    this->date = QDate::currentDate();
    QDateEdit* dateEdit = new QDateEdit(QDate::currentDate());
    connect(dateEdit, &QDateEdit::userDateChanged, dateEdit, [=](const QDate &date) {
        this->date = date;
    });
    formLayout->addRow(new QLabel("Дата:"), dateEdit);

    const QStringList list = QStringList({"Скалистый", "123"});
    this->rudnik = list.at(0);
    QComboBox* rudnikEdit = new QComboBox();
    rudnikEdit->setModel(new QStringListModel(list));
    formLayout->addRow(new QLabel("Рудник:"), rudnikEdit);
    connect(rudnikEdit, &QComboBox::currentTextChanged, rudnikEdit, [=](const QString &text) {
        this->rudnik = text;
    });

    QLineEdit* nameVirabEdit = new QLineEdit();
    formLayout->addRow(new QLabel("Название выроботки:"), nameVirabEdit);
    connect(nameVirabEdit, &QLineEdit::textChanged, nameVirabEdit, [=](const QString &text) {
        this->nameVirab = text;
    });

    QLineEdit* IzmVipEdit = new QLineEdit();
    formLayout->addRow(new QLabel("Измерение выполнил:"), IzmVipEdit);
    connect(IzmVipEdit, &QLineEdit::textChanged, IzmVipEdit, [=](const QString &text) {
        this->izmVip = text;
    });

    this->XX = 0;
    QSpinBox* XXEdit = new QSpinBox();
    formLayout->addRow(new QLabel("XX:"), XXEdit);
    connect(XXEdit, QOverload<int>::of(&QSpinBox::valueChanged), XXEdit, [=](int num) {
        this->XX = num;
    });

    this->YY = 0;
    QSpinBox* YYEdit = new QSpinBox();
    formLayout->addRow(new QLabel("YY:"), YYEdit);
    connect(YYEdit, QOverload<int>::of(&QSpinBox::valueChanged), YYEdit, [=](int num) {
        this->YY = num;
    });

    this->ZZ = 0;
    QSpinBox* ZZEdit = new QSpinBox();
    formLayout->addRow(new QLabel("ZZ:"), ZZEdit);
    connect(ZZEdit, QOverload<int>::of(&QSpinBox::valueChanged), ZZEdit, [=](int num) {
        this->ZZ = num;
    });

    this->setLayout(formLayout);
    this->setFixedWidth(310);

    QPushButton* btn = new QPushButton("Сохранить в XML");
    connect(btn, &QPushButton::clicked, this, &WidgetXML::clickedSave);
    formLayout->addItem(new QSpacerItem(0, 10));
    formLayout->addWidget(btn);

    QPushButton* btnDocx = new QPushButton("Сохранить в docx");
    connect(btnDocx, &QPushButton::clicked, this, &WidgetXML::createDocx);
    formLayout->addWidget(btnDocx);


}

DataWgtXML WidgetXML::getData()
{
    DataWgtXML dataWgtXml;
    dataWgtXml.date = date;
    dataWgtXml.rudnik = rudnik;
    dataWgtXml.nameVirab = nameVirab;
    dataWgtXml.izmVip = izmVip;
    dataWgtXml.XX = XX;
    dataWgtXml.YY = YY;
    dataWgtXml.ZZ = ZZ;

    return dataWgtXml;
}

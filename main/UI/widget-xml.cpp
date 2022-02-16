#include "widget-xml.h"

#include <QDate>
#include <QDateEdit>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>

WidgetXML::WidgetXML(QWidget *parent) : QWidget(parent)
{
    QFormLayout* formLayout = new QFormLayout();

    QDateEdit* dateEdit = new QDateEdit(QDate::currentDate());
    connect(dateEdit, &QDateEdit::userDateChanged, dateEdit, [=](const QDate &date) {
        this->date = date;
    });
    formLayout->addRow(new QLabel("Дата:"), dateEdit);

    QLineEdit* rudnikEdit = new QLineEdit();
    formLayout->addRow(new QLabel("Рудник:"), rudnikEdit);
    connect(rudnikEdit, &QLineEdit::textChanged, rudnikEdit, [=](const QString &text) {
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

    QSpinBox* XXEdit = new QSpinBox();
    formLayout->addRow(new QLabel("XX:"), XXEdit);
    connect(XXEdit, QOverload<int>::of(&QSpinBox::valueChanged), XXEdit, [=](int num) {
        this->XX = num;
    });

    QSpinBox* YYEdit = new QSpinBox();
    formLayout->addRow(new QLabel("YY:"), YYEdit);
    connect(YYEdit, QOverload<int>::of(&QSpinBox::valueChanged), YYEdit, [=](int num) {
        this->YY = num;
    });

    QSpinBox* ZZEdit = new QSpinBox();
    formLayout->addRow(new QLabel("YY:"), ZZEdit);
    connect(ZZEdit, QOverload<int>::of(&QSpinBox::valueChanged), ZZEdit, [=](int num) {
        this->ZZ = num;
    });

    this->setLayout(formLayout);
    this->setFixedWidth(250);

    QPushButton* btn = new QPushButton("Сохранить в XML");
    connect(btn, &QPushButton::clicked, this, &WidgetXML::clickedSave);
    formLayout->addItem(new QSpacerItem(0, 10));
    formLayout->addWidget(btn);
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

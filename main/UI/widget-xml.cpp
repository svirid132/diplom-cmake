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
#include "../preloader/initStyles.h"

WidgetXML::WidgetXML(QWidget *parent) : QWidget(parent)
{
    QFormLayout* formLayout = new QFormLayout();

    this->date = QDate::currentDate();
    QDateEdit* dateEdit = new QDateEdit(QDate::currentDate());
//    dateEdit->setObjectName("date");
    SettingsUI::dateTimeEdit(dateEdit);
    connect(dateEdit, &QDateEdit::userDateChanged, dateEdit, [=](const QDate &date) {
        this->date = date;
    });
    formLayout->addRow(new QLabel("Дата:"), dateEdit);

    const QStringList list = QStringList({"Скалистый", "Комсомольский", "Октябрьский", "Таймырский"});
    this->rudnik = list.at(0);
    QComboBox* rudnikEdit = new QComboBox();
    rudnikEdit->setModel(new QStringListModel(list));
    formLayout->addRow(new QLabel("Рудник:"), rudnikEdit);
    connect(rudnikEdit, &QComboBox::currentTextChanged, rudnikEdit, [=](const QString &text) {
        rudnikEdit->setStyleSheet("");
        this->rudnik = text;
    });

    QLineEdit* nameVirabEdit = new QLineEdit();
    formLayout->addRow(new QLabel("Название выроботки:"), nameVirabEdit);
    connect(nameVirabEdit, &QLineEdit::textChanged, nameVirabEdit, [=](const QString &text) {
        nameVirabEdit->setStyleSheet("");
        this->nameVirab = text;
    });

    QLineEdit* IzmVipEdit = new QLineEdit();
    QLabel* lengthLabel = new QLabel("Измерение выполнил:");
    formLayout->addRow(lengthLabel, IzmVipEdit);
    int lengthLabelWidth = lengthLabel->minimumSizeHint().width();
    connect(IzmVipEdit, &QLineEdit::textChanged, IzmVipEdit, [=](const QString &text) {
        IzmVipEdit->setStyleSheet("");
        this->izmVip = text;
    });

    const double max = 55000.9;
    const double min = -55000.9;
    const int decimals = 1;
    this->XX = 0;
    QDoubleSpinBox* XXEdit = new QDoubleSpinBox();
    SettingsUI::doubleSpinBox(XXEdit);
    XXEdit->setMaximum(max);
    XXEdit->setMinimum(min);
    XXEdit->setDecimals(decimals);
    formLayout->addRow(new QLabel("XX:"), XXEdit);
    connect(XXEdit, QOverload<double>::of(&QDoubleSpinBox::valueChanged), XXEdit, [=](double num) {
        this->XX = num;
    });

    this->YY = 0;
    QDoubleSpinBox* YYEdit = new QDoubleSpinBox();
    SettingsUI::doubleSpinBox(YYEdit);
    YYEdit->setMaximum(max);
    YYEdit->setMinimum(min);
    YYEdit->setDecimals(decimals);
    formLayout->addRow(new QLabel("YY:"), YYEdit);
    connect(YYEdit, QOverload<double>::of(&QDoubleSpinBox::valueChanged), YYEdit, [=](double num) {
        this->YY = num;
    });

    this->ZZ = 0;
    QDoubleSpinBox* ZZEdit = new QDoubleSpinBox();
    SettingsUI::doubleSpinBox(ZZEdit);
    ZZEdit->setDecimals(decimals);
    ZZEdit->setMaximum(max);
    ZZEdit->setMinimum(min);
    formLayout->addRow(new QLabel("ZZ:"), ZZEdit);
    connect(ZZEdit, QOverload<double>::of(&QDoubleSpinBox::valueChanged), ZZEdit, [=](double num) {
        this->ZZ = num;
    });

    QPushButton* btnXML = new QPushButton("Сохранить в XML");
    connect(btnXML, &QPushButton::clicked, [=]() {
        QString styleSheet = "background-color: red;";
        bool ok = true;
        if (nameVirab == "") {
            nameVirabEdit->setStyleSheet(styleSheet);
            ok = false;
        } else if (izmVip == "") {
            IzmVipEdit->setStyleSheet(styleSheet);
            ok = false;
        }

        if (ok) emit this->clickedSave();
    });
    formLayout->addItem(new QSpacerItem(0, 10));
    formLayout->addWidget(btnXML);

    QPushButton* btnDocx = new QPushButton("Сохранить в docx");
    connect(btnDocx, &QPushButton::clicked, btnDocx, [=]() {
        QString styleSheet = "background-color: red;";
        bool ok = true;
        if (nameVirab == "") {
            nameVirabEdit->setStyleSheet(styleSheet);
            ok = false;
        }

        if(ok) emit this->createDocx();
    });

//    formLayout->setAlignment(Qt::AlignJustify);
//    formLayout->setRowWrapPolicy(QFormLayout::WrapLongRows);
    btnCommission = new QPushButton("Состав Коммисии");
    connect(btnCommission, &QPushButton::clicked, [=]() {
        btnCommission->setStyleSheet("");
        emit this->clickedCommission();
    });
    btnCommission->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Maximum);
    formLayout->addRow(btnCommission, btnDocx);
//    formLayout->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);

//    QPushButton* btnConverter = new QPushButton("Конвер. XML в DOCX");
//    connect(btnConverter, &QPushButton::clicked, this, &WidgetXML::clickedXmlToDocx);
//    formLayout->addWidget(btnConverter);


    this->setLayout(formLayout);
    this->setFixedWidth(390);
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

void WidgetXML::errorCommission() {
    QString style = "background-color: red;";
    btnCommission->setStyleSheet(style);
}

#include "widgetmain.h"

#include <QChartView>
#include <QDebug>
#include <QDialog>
#include <QFileDialog>
#include <QFormLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QTextEdit>
#include <qchartview.h>
#include <qchartview.h>
#include "../global-var.h"
#include "../preloader/initStyles.h"

WidgetMain::WidgetMain(QWidget *parent)
    : QWidget{parent},
      successResult({1, 1, 1}),
      middleResult({1, 1, 1}),
      isError(false),
      secondWidget(nullptr),
      layout(new QHBoxLayout())
{
//    layout->setSpacing(5);
//    layout->setMargin(5);

    QFormLayout *layoutPanel = new QFormLayout;
    layoutPanel->setVerticalSpacing(10);
    fillLayoutPanel(layoutPanel);

    QWidget* panelWidget = new QWidget();
    panelWidget->setLayout(layoutPanel);

    leftPanel = new QScrollArea();
    leftPanel->setWidgetResizable(true);
//    leftPanel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    leftPanel->setWidget(panelWidget);
    leftPanel->setFixedWidth(220);
//    leftPanel->setFixedHeight(300);

    layout->addWidget(leftPanel);
    this->setLayout(layout);
}

void WidgetMain::errorFile()
{
    selectButton->setStyleSheet("background-color: red;");
}

void WidgetMain::errorPeriod()
{
    spinBoxPeriod->setStyleSheet("background-color: red");
}

void WidgetMain::setKoefZapCategory(float koefZap, QString category)
{
    QString num = tr("Коэф.зап: ") + QString::number(koefZap);
    QString fullCategory = "Категоря: " + category;
    labelKoefZap->setText(num);
    labelCategory->setText(fullCategory);
}

void WidgetMain::setLabelFilename(const QString& path, bool preChange)
{
    int positionFilename = path.lastIndexOf("/") + 1;
    if (preChange) setEnabledXMLbtn(false);
    QString filename = path.mid(positionFilename);
    const int wordWidth = 15;
    const int countPath = filename.size() / wordWidth;
    for (int i = 0; i < countPath; ++i) {
        filename.insert(wordWidth * (i + 1) + i, '\n');
    }

    if (preChange) {
        QFont font = labelFile->font();
        font.setUnderline(true);
        labelFile->setFont(font);
    } else {
        QFont font = labelFile->font();
        font.setUnderline(false);
        labelFile->setFont(font);
    }

    selectButton->setStyleSheet("");
    labelFile->setText(filename);
}

void WidgetMain::fillLayoutPanel(QFormLayout *const layout)
{
    layout->setSizeConstraint(QLayout::SetFixedSize);

    labelsLsh = new QLabel(strLsh);
    labelsh = new QLabel(strh);
    QDoubleSpinBox* spinBoxLsh = new QDoubleSpinBox;
    QDoubleSpinBox* spinBoxh = new QDoubleSpinBox;
    SettingsUI::doubleSpinBox(spinBoxLsh);
    SettingsUI::doubleSpinBox(spinBoxh);
    spinBoxLsh->setMinimum(1);
    spinBoxh->setMinimum(1);

    QFormLayout* formLayout = new QFormLayout();
    formLayout->setMargin(0);
    formLayout->setSpacing(10);
    formLayout->setHorizontalSpacing(40);
    formLayout->addRow(labelsLsh, spinBoxLsh);
    formLayout->addRow(labelsh, spinBoxh);
    QWidget* formWid = new QWidget();
    formWid->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Maximum);
    formWid->setLayout(formLayout);
    layout->addRow(formWid);
    layout->addItem(new QSpacerItem(0, 3));

    connect(spinBoxLsh, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [=](double value) {
        middleResult.Lsh = float(value);
        if (middleResult.Lsh != successResult.Lsh) {
            QFont f = labelsLsh->font();
            f.setUnderline(true);
            labelsLsh->setFont(f);
        } else {
            QFont font = labelsLsh->font();
            font.setUnderline(false);
            labelsLsh->setFont(font);
        }

        updateEnabledXMLbtn();
    });
    connect(spinBoxh, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [=](double value) {
        middleResult.h = float(value);
        if (middleResult.h != successResult.h) {
            QFont f = labelsLsh->font();
            f.setUnderline(true);
            labelsh->setFont(f);
        } else {
            QFont font = labelFile->font();
            font.setUnderline(false);
            labelsh->setFont(font);
        }
        updateEnabledXMLbtn();
    });

    selectButton = new QPushButton("Обзор");
    selectButton->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum));
    connect(selectButton, &QPushButton::clicked, this, &WidgetMain::openFile);

    labelFile = new QLabel("");
    labelFile->setStyleSheet("padding: 2px;");
    labelFile->setSizePolicy(QSizePolicy(QSizePolicy::Ignored, QSizePolicy::Minimum));
    QVBoxLayout* vertical = new QVBoxLayout();
    vertical->addWidget(labelFile);
    vertical->addWidget(selectButton);
    vertical->setSpacing(10);
    QGroupBox* groupBox = new QGroupBox(this);
    groupBox->setTitle("Выбор raw файла");
    groupBox->setLayout(vertical);
    layout->addRow(groupBox);
    groupBox->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    labelPeriod = new QLabel(strPeriod);
    spinBoxPeriod = new QSpinBox;
    spinBoxPeriod->setMinimum(1);
    SettingsUI::spinBox(spinBoxPeriod);
    connect(spinBoxPeriod, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int num){
        spinBoxPeriod->setStyleSheet("");
        middleResult.period = num;
        if (middleResult.period != successResult.period) {
            QFont f = labelsLsh->font();
            f.setUnderline(true);
            labelPeriod->setFont(f);
        } else {
            QFont font = labelFile->font();
            font.setUnderline(false);
            labelPeriod->setFont(font);
        }

        updateEnabledXMLbtn();
    });
    layout->addRow(labelPeriod, spinBoxPeriod);

    layout->addItem(new QSpacerItem(0, 5));

    QVBoxLayout* boxLayout = new QVBoxLayout();
    labelKoefZap = new QLabel("Коэф.зап:");
    labelCategory = new QLabel("Категоря:");
    boxLayout->setSpacing(5);
    boxLayout->addWidget(labelKoefZap);
    boxLayout->addWidget(labelCategory);
    QGroupBox* groupLabel = new QGroupBox("Результат");
    groupLabel->setLayout(boxLayout);
    layout->addRow(groupLabel);

    layout->addItem(new QSpacerItem(0, 5));


    QPushButton* executeButton = new QPushButton("Вычислить");
    layout->addRow(executeButton);
    connect(executeButton, &QPushButton::clicked, this, [=](){
        emit executeAPI(middleResult.Lsh, middleResult.h, middleResult.period, filenameAPI);
    });

    QPushButton* fromXmlbtn = new QPushButton("Вычислить из XML");
    layout->addRow(fromXmlbtn);
    connect(fromXmlbtn, &QPushButton::clicked, this, [=](){
        emit fromXml();
    });

    blockingWdgs << spinBoxLsh << spinBoxh << groupBox << spinBoxPeriod << executeButton << fromXmlbtn;

    XMLbtn = new QPushButton("Создать файл");
    connect(XMLbtn, QOverload<bool>::of(&QPushButton::clicked), this, &WidgetMain::clickedSaveXML);
    XMLbtn->setCheckable(true);
    layout->addRow(XMLbtn);
}

bool WidgetMain::isChange()
{
    return !(middleResult.Lsh == successResult.Lsh && middleResult.h == successResult.h
             && middleResult.period == successResult.period);
}

void WidgetMain::updateEnabledXMLbtn()
{
    if (isChange()){
        setEnabledXMLbtn(false);
    } else {
        setEnabledXMLbtn(true);
    }
}

void WidgetMain::openFile()
{
    QFileDialog dialog;
    const QString filter = "Raw files (*.raw)";
    dialog.setNameFilter(filter);
    int width = 500;
    int height = 400;
    dialog.setGeometry(
                WIDTH_SCREEN / 2 - width / 2,
                HEIGHT_SCREEN / 2 - height / 2,
                width,
                height);
    if (dialog.exec()) {
        filenameAPI = dialog.selectedFiles().at(0);
        setLabelFilename(filenameAPI);
    }
}

QString WidgetMain::openFileXml() {
    QFileDialog dialog;
    const QString filter = "xml files (*.xml)";
    dialog.setNameFilter(filter);
    int width = 500;
    int height = 400;
    dialog.setGeometry(
            WIDTH_SCREEN / 2 - width / 2,
            HEIGHT_SCREEN / 2 - height / 2,
            width,
            height);
    if (dialog.exec() == QDialog::Accepted) { // accept = 1
        QString filename = dialog.selectedFiles().at(0);
        return filename;
    }

    return "";
}

void WidgetMain::setWidget(QWidget* widget) {
    if (!secondWidget) {
        layout->addWidget(widget);
    }
    layout->replaceWidget(secondWidget, widget);
    widget->show();
    if(secondWidget) secondWidget->hide();
    secondWidget = widget;
}

void WidgetMain::successChange() {
    labelsLsh->setText(strLsh);
    labelsh->setText(strh);
    setLabelFilename(filenameAPI, false);
    labelPeriod->setText(strPeriod);

    setEnabledXMLbtn(true);
}

void WidgetMain::setEnabledXMLbtn(bool flag)
{
    XMLbtn->setEnabled(flag);
}

void WidgetMain::setEnabledPanel(bool flag) {
    XMLbtn->setText(flag ? "Создать XML" : "Отменить сохр. XML");
    for (auto&& wdg: blockingWdgs) {
        wdg->setEnabled(flag);
    }
}

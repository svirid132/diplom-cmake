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
#include "global-var.h"

WidgetMain::WidgetMain(QWidget *parent)
    : QWidget{parent},
      successResult({1, 1, 1}),
      middleResult({1, 1, 1}),
      isError(false),
      secondWidget(nullptr),
      layout(new QHBoxLayout())
{
    layout->setSpacing(5);
    layout->setMargin(10);

    QFormLayout *layoutPanel = new QFormLayout;
    layoutPanel->setVerticalSpacing(10);
    fillLayoutPanel(layoutPanel);
    leftPanel = new QWidget();
    leftPanel->setLayout(layoutPanel);
    leftPanel->setFixedWidth(190);

    layout->addWidget(leftPanel);
    this->setLayout(layout);
}

void WidgetMain::errorFile()
{
    labelFile->setStyleSheet("background-color: red; padding: 2px;");
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
    QString strChange = preChange ? this->preChange : "";
    QString filename = strChange + path.mid(positionFilename);
    const int wordWidth = 15;
    const int countPath = filename.size() / wordWidth;
    for (int i = 0; i < countPath; ++i) {
        filename.insert(wordWidth * (i + 1) + i, '\n');
    }
    labelFile->setStyleSheet("padding: 2px;");
    labelFile->setText(filename);
}

void WidgetMain::fillLayoutPanel(QFormLayout *const layout)
{
    labelsLsh = new QLabel(strLsh);
    labelsh = new QLabel(strh);
    QDoubleSpinBox* spinBoxLsh = new QDoubleSpinBox;
    QDoubleSpinBox* spinBoxh = new QDoubleSpinBox;
    spinBoxLsh->setMinimum(1);
    spinBoxh->setMinimum(1);
    layout->addRow(labelsLsh, spinBoxLsh);
    layout->addRow(labelsh, spinBoxh);
    connect(spinBoxLsh, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [=](double value) {
        middleResult.Lsh = float(value);
        if (middleResult.Lsh == successResult.Lsh) {
            labelsLsh->setText(strLsh);
        } else {
            labelsLsh->setText(preChange + strLsh);
        }
        updateEnabledXMLbtn();
    });
    connect(spinBoxh, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [=](double value) {
        middleResult.h = float(value);
        if (middleResult.h == successResult.h) {
            labelsh->setText(strh);
        } else {
            labelsh->setText(preChange + strh);
        }
        updateEnabledXMLbtn();
    });

    QPushButton* selectButton = new QPushButton("Обзор");
    selectButton->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum));
    connect(selectButton, &QPushButton::clicked, this, &WidgetMain::openFile);
    labelFile = new QLabel();
    labelFile->setSizePolicy(QSizePolicy(QSizePolicy::Ignored, QSizePolicy::Minimum));
    QVBoxLayout* vertical = new QVBoxLayout();
    vertical->addWidget(labelFile);
    vertical->addWidget(selectButton);
    QGroupBox* groupBox = new QGroupBox(this);
    groupBox->setTitle("Выбор файла");
    groupBox->setLayout(vertical);
    layout->addRow(groupBox);

    labelPeriod = new QLabel(strPeriod + skip);
    spinBoxPeriod = new QSpinBox;
    spinBoxPeriod->setMinimum(1);
    connect(spinBoxPeriod, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int num){
        spinBoxPeriod->setStyleSheet("");
        middleResult.period = num;
        if (middleResult.period == successResult.period) {
            labelPeriod->setText(strPeriod + skip);
        } else {
            labelPeriod->setText(preChange + strPeriod);
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

    QPushButton* executeButton = new QPushButton("Выполнить");
    layout->addRow(executeButton);
    connect(executeButton, &QPushButton::clicked, this, [=](){
        emit executeAPI(middleResult.Lsh, middleResult.h, middleResult.period, filenameAPI);
    });

    blockingWdgs << spinBoxLsh << spinBoxh << groupBox << spinBoxPeriod << executeButton;

    XMLbtn = new QPushButton("Создать XML");
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

void WidgetMain::setWidget(QWidget* widget) {
    if (secondWidget) secondWidget->hide();
    widget->show();
    layout->removeWidget(secondWidget);
    layout->addWidget(widget);
    secondWidget = widget;;
}

void WidgetMain::successChange() {
    labelsLsh->setText(strLsh);
    labelsh->setText(strh);
    setLabelFilename(filenameAPI, false);
    labelPeriod->setText(strPeriod + skip);

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

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
      Lsh(1),
      h(1),
      period(1),
      isError(false),
      layout(new QHBoxLayout()),
      secondWidget(nullptr)
{
    layout->setSpacing(5);
    layout->setMargin(10);

    QVBoxLayout* vertical = new QVBoxLayout();
//    vertical->setDirection(QBoxLayout::Down);
//    vertical->setSpacing(0);
//    vertical->setMargin(0);

    QFormLayout *layoutPanel = new QFormLayout;
    layoutPanel->setVerticalSpacing(10);
//    layoutPanel->setMargin(0);
    fillLayoutPanel(layoutPanel);
    leftPanel = new QWidget();
    leftPanel->setLayout(layoutPanel);
    leftPanel->setFixedWidth(190);

//    leftPanel->setStyleSheet("background-color: red");

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

void WidgetMain::setLabelFilename(const QString& path)
{
    int positionFilename = path.lastIndexOf("/") + 1;
    QString filename = path.mid(positionFilename);
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
    QLabel* labelsLsh = new QLabel(tr("Lsh:"));
    QLabel* labelsh = new QLabel(tr("h:"));
    QDoubleSpinBox* spinBoxLsh = new QDoubleSpinBox;
    QDoubleSpinBox* spinBoxh = new QDoubleSpinBox;
    spinBoxLsh->setMinimum(1);
    spinBoxh->setMinimum(1);
    layout->addRow(labelsLsh, spinBoxLsh);
    layout->addRow(labelsh, spinBoxh);
    connect(spinBoxLsh, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [=](double value) {
        Lsh = float(value);
    });
    connect(spinBoxh, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [=](double value) {
        h = float(value);
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

    QLabel* labelPeriod = new QLabel(tr("Period(sec):"));
    spinBoxPeriod = new QSpinBox;
    spinBoxPeriod->setMinimum(1);
    connect(spinBoxPeriod, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int num){
        spinBoxPeriod->setStyleSheet("");
        period = num;
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
        emit executeAPI(Lsh, h, period, filenameAPI);
    });

    blockingWdgs << spinBoxLsh << spinBoxh << groupBox << spinBoxPeriod << executeButton;

    XMLbtn = new QPushButton("Создать XML");
    connect(XMLbtn, QOverload<bool>::of(&QPushButton::clicked), this, &WidgetMain::clickedSaveXML);
//    XMLbtn->setEnabled(false);
    XMLbtn->setCheckable(true);
    layout->addRow(XMLbtn);
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

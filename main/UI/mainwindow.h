#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "UI-var.h"
#include "../preloader/preloader-var.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setCentralWidget(QWidget* widget);

    void setDocxPath(const QString& path);

    void setDataCommission(const DataCommission& data);
    bool isDataCommission();
    DataCommission getDataCommission();

    void setDialogConverter(std::function<QString(const DialogParam& param, const QString& docxPath, bool& ok)> dialog);
    void setDialogCommission(std::function<DataCommission(const DialogParam& param, const DataCommission& data, bool& ok)> diloag);
    void dialogCommission();
    void dialogConveter();

    void viewError(const QString &str);
    void viewSuccess(const QString& str);

    bool dialogQuestion(const QString& propblem, const QString& question);

private:
    Ui::MainWindow *ui;
    DataCommission dataCommission;
    std::function<DataCommission(const DialogParam& param, const DataCommission& data, bool& ok)> openCommissionDialog;
    std::function<QString(const DialogParam& param, const QString& docxPath, bool& ok)> openConverterDialog;
    QString docxPath;
};
#endif // MAINWINDOW_H

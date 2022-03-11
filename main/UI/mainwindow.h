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

    void setDataCommission(const DataCommission& data);
    bool isDataCommission();
    DataCommission getDataCommission();

    void setDialogCommission(std::function<DataCommission(const DialogParam& param, const DataCommission& data, bool& ok)> diloag);
    void dialogCommission();

    void viewError(const QString &str);
    void viewSuccess(const QString& str);

private:
    Ui::MainWindow *ui;
    DataCommission dataCommission;
    std::function<DataCommission(const DialogParam& param, const DataCommission& data, bool& ok)> openCommissionDialog;
};
#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

    void viewError(const QString &str);
    void viewSuccess(const QString& str);
    void commissionDialog();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

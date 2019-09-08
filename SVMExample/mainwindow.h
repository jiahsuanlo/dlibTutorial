#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "svmtest.h"
#include <QFileDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButtonTrain_clicked();

    void on_pushButtonTestSample_clicked();

    void on_pushButtonSaveModel_clicked();

    void on_pushButtonLoadModel_clicked();

    void on_pushButtonReduceCrossValidate_clicked();

    void on_pushButtonReduceFunction_clicked();

private:
    Ui::MainWindow *ui;

    svt::SVMTester svmtester_;
};

#endif // MAINWINDOW_H

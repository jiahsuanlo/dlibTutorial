#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    svmtester_.CrossValidationCheck();

}

void MainWindow::on_pushButtonTrain_clicked()
{
    double C= ui->lineEditC->text().toDouble();
    double gamma= ui->lineEditGamma->text().toDouble();
    svmtester_.Train(C, gamma);
    svmtester_.TrainPFunction(C,gamma);
}

void MainWindow::on_pushButtonTestSample_clicked()
{
    svt::SVMTester::sample_type samp;
    samp(0)= ui->lineEditSample0->text().toDouble();
    samp(1)= ui->lineEditSample1->text().toDouble();

    svmtester_.TestOneSample(samp);

}

void MainWindow::on_pushButtonSaveModel_clicked()
{
    QString filename= QFileDialog::getSaveFileName(this, tr("Save Model File"),
                                                   ".",
                                                   tr("Data file (*.dat)"));

    svmtester_.SaveModel(filename);
}

void MainWindow::on_pushButtonLoadModel_clicked()
{
    QString filename= QFileDialog::getOpenFileName(this, tr("Load Model File"),
                                                   ".",
                                                   tr("Data file (*.dat)"));
    svmtester_.LoadModel(filename);
}

void MainWindow::on_pushButtonReduceCrossValidate_clicked()
{
    int num_vectors= ui->lineEditSVCount->text().toInt();
    int fold= ui->lineEditFoldCount->text().toInt();

    svmtester_.CrossValidateReduced(num_vectors, fold);

}

void MainWindow::on_pushButtonReduceFunction_clicked()
{
    int num_vectors= ui->lineEditSVCount->text().toInt();
    int fold= ui->lineEditFoldCount->text().toInt();
    svmtester_.ReduceModel(num_vectors, fold);
}

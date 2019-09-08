#include "digitrecognitionapp.h"
#include "ui_digitrecognitionapp.h"

DigitRecognitionApp::DigitRecognitionApp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DigitRecognitionApp)
{
    ui->setupUi(this);
}

DigitRecognitionApp::~DigitRecognitionApp()
{
    delete ui;
}

void DigitRecognitionApp::on_pushButtonStart_clicked()
{
    dp::DigitPredictor digitpred;

    digitpred.Test("./data");
}

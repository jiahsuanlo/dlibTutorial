#include "digitrecognitionapp.h"
#include "ui_digitrecognitionapp.h"

DigitRecognitionApp::DigitRecognitionApp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DigitRecognitionApp),
    digitpred_(dp::DigitPredictorParams())
{
    ui->setupUi(this);
}

DigitRecognitionApp::~DigitRecognitionApp()
{
    delete ui;
}

void DigitRecognitionApp::on_pushButtonStart_clicked()
{
    digitpred_.Train();

    ui->pushButtonSaveModel->setEnabled(true);
}

void DigitRecognitionApp::on_pushButtonSelectDirectory_clicked()
{
    QString in_dir= QFileDialog::getExistingDirectory(this, tr("Select Mnist Data Folder"));

    // load data now
    digitpred_.LoadData(in_dir);

    // show on line edit
    ui->lineEditDataDirectory->setText(in_dir);

    // enable gui
    ui->groupBoxTrainer->setEnabled(true);
    ui->pushButtonStart->setEnabled(true);    
}

void DigitRecognitionApp::on_lineEditLearnRate_textChanged(const QString &arg1)
{
    dp::DigitPredictorParams &params= digitpred_.Params();
    bool ok;
    double newlr= arg1.toDouble(&ok);
    if (ok)
    {
        params.learning_rate= newlr;
        digitpred_.SetTrainerSettings();
    }
}

void DigitRecognitionApp::on_lineEditMiniLearnRate_textChanged(const QString &arg1)
{
    dp::DigitPredictorParams &params= digitpred_.Params();
    bool ok;
    double newmlr= arg1.toDouble(&ok);
    if (ok)
    {
        params.mini_learning_rate= newmlr;
        digitpred_.SetTrainerSettings();
    }
}

void DigitRecognitionApp::on_lineEditMiniBatchSize_textChanged(const QString &arg1)
{
    dp::DigitPredictorParams &params= digitpred_.Params();
    bool ok;
    unsigned long newbs= arg1.toULong(&ok);
    if (ok)
    {
        params.minibatch_size= newbs;
        digitpred_.SetTrainerSettings();
    }
}

void DigitRecognitionApp::on_lineEditMnistSync_textChanged(const QString &arg1)
{
    dp::DigitPredictorParams &params= digitpred_.Params();
    params.sync_filename= arg1.toStdString();
    digitpred_.SetTrainerSettings();
}



void DigitRecognitionApp::on_checkBoxVerbose_toggled(bool checked)
{
    dp::DigitPredictorParams &params= digitpred_.Params();
    params.trainer_verbose= checked;
    digitpred_.SetTrainerSettings();
}

void DigitRecognitionApp::on_lineEditSyncSec_textChanged(const QString &arg1)
{
    dp::DigitPredictorParams &params= digitpred_.Params();
    bool ok;
    int newsec= arg1.toInt(&ok);
    if (ok)
    {
        params.sync_sec= newsec;
        digitpred_.SetTrainerSettings();
    }
}

void DigitRecognitionApp::on_pushButtonSaveModel_clicked()
{
    QString filename= QFileDialog::getSaveFileName(this,
                                 tr("Save Model File"),
                                 "",
                                 tr("Data file (*.dat)"));

    digitpred_.SaveModel(filename);

}

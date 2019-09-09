#ifndef DIGITRECOGNITIONAPP_H
#define DIGITRECOGNITIONAPP_H

#include <QMainWindow>
#include "digitpredictor.h"
#include <QFileDialog>

namespace Ui {
class DigitRecognitionApp;
}

class DigitRecognitionApp : public QMainWindow
{
    Q_OBJECT

public:
    explicit DigitRecognitionApp(QWidget *parent = nullptr);
    ~DigitRecognitionApp();

private slots:
    void on_pushButtonStart_clicked();

    void on_pushButtonSelectDirectory_clicked();

    void on_lineEditLearnRate_textChanged(const QString &arg1);

    void on_lineEditMiniLearnRate_textChanged(const QString &arg1);

    void on_lineEditMiniBatchSize_textChanged(const QString &arg1);

    void on_lineEditMnistSync_textChanged(const QString &arg1);

    void on_checkBoxVerbose_toggled(bool checked);

    void on_lineEditSyncSec_textChanged(const QString &arg1);

    void on_pushButtonSaveModel_clicked();

private:
    Ui::DigitRecognitionApp *ui;

    // ==== digit recognition ====
    dp::DigitPredictor digitpred_;
};

#endif // DIGITRECOGNITIONAPP_H

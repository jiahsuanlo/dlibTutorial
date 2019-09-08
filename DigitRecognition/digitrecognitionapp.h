#ifndef DIGITRECOGNITIONAPP_H
#define DIGITRECOGNITIONAPP_H

#include <QMainWindow>
#include "digitpredictor.h"

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

private:
    Ui::DigitRecognitionApp *ui;
};

#endif // DIGITRECOGNITIONAPP_H

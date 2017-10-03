#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>

extern "C" {
#include "../arduino-serial/arduino-serial-lib.h"
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_Interface->setText("/dev/ttyACM0");
    ui->pushButton_GetInf->setDisabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;

    if (worker != 0 && worker->isRunning() ) {
        worker->requestInterruption();
        worker->wait();
        serialport_close(this->fileDescriptor);
    }
}

void MainWindow::writeToSerial(const char *message)
{
    serialport_write(this->fileDescriptor, message);
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_pushButton_Initialize_clicked()
{
    int ret;

    // https://wiki.qt.io/Technical_FAQ#How_can_I_convert_a_QString_to_char.2A_and_vice_versa.3F
    QByteArray ba = ui->lineEdit_Interface->text().toLocal8Bit();
    const char *c_str = ba.data();

    ret = serialport_init(c_str, (int)ui->comboBox->currentText().toInt());

    if (ret == -1){
        ui->statusBar->showMessage("Failed to initialize Serial Port");
    }
    else{
        this->fileDescriptor = ret;

        this->worker = new ReadWorker(ret);
        connect(worker, SIGNAL(somethingToTell(QString)), this, SLOT(on_somethingToTell(QString)));
        worker->start();

        ui->statusBar->showMessage("Serial Port initialized.");
        ui->pushButton_GetInf->setDisabled(false);
    }
}

void MainWindow::on_somethingToTell(QString text)
{
    //ui->textBrowser->append(text);
    ui->textBrowser->insertPlainText(text);
}

void MainWindow::on_pushButton_GetInf_clicked()
{
    //serialport_write(this->fileDescriptor, "i");
    writeToSerial("i");
}

void MainWindow::on_pushButton_SendCmd_clicked()
{
    QByteArray ba = ui->lineEdit_Cmd->text().toLocal8Bit();
    const char *c_str = ba.data();
    writeToSerial(c_str);
}

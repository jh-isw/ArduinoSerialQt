#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <readworker.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionQuit_triggered();

    void on_pushButton_Initialize_clicked();

    void on_somethingToTell(QString text);

    void on_pushButton_GetInf_clicked();

    void on_pushButton_SendCmd_clicked();

private:
    Ui::MainWindow *ui;
    int fileDescriptor;
    ReadWorker *worker;

    void writeToSerial(const char*);
};

#endif // MAINWINDOW_H

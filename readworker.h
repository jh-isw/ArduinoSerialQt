#ifndef READWORKER_H
#define READWORKER_H

#include <QThread>

class ReadWorker : public QThread
{
    Q_OBJECT
public:
    explicit ReadWorker(QObject *parent = 0);
    ReadWorker(int fileDescr);

private:
    int fileDescriptor;
    void run();

signals:
    void somethingToTell(QString text);
};

#endif // READWORKER_H

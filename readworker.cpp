#include "readworker.h"
#include <unistd.h>
#include <QtDebug>

ReadWorker::ReadWorker(QObject *parent) : QThread(parent)
{

}

ReadWorker::ReadWorker(int fileDescr)
{
    this->fileDescriptor = fileDescr;
}

void ReadWorker::run()
{
    char buf[255];
    //int bufOffset = 0;
    int retVal;
    //QString message = "";

    while(!isInterruptionRequested()) {
        retVal = read(this->fileDescriptor, buf, 255);

        if (retVal > 0){
            //message += QString(buf);
            //qDebug() << buf;
            buf[retVal] = '\0';
            emit somethingToTell(QString(buf));
        }
    }
}


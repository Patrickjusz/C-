#include "mythread.h"
#include <QtCore>
#include <QString>
MyThread::MyThread(QObject *parent) :
    QThread(parent)
{
}

void MyThread::run() {
    this->Stop=false;
    QFile file("C:\\Users\\Patryk\\Desktop\\slownik.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QString hash;
    QMutex mutex;
    QByteArray line;
    int licznik=0;
    while (!file.atEnd()) {
        //if (this->Stop) break;
        //mutex.lock();

       // if (this->Stop) break;




        line = file.readLine().simplified();
        licznik++;
        switch( this->hashJaki )
        {
        case 0:
            hash = QString(QCryptographicHash::hash((line),QCryptographicHash::Md4).toHex());
            break;

        case 1:
            hash = QString(QCryptographicHash::hash((line),QCryptographicHash::Md5).toHex());
            break;


        case 2:
            hash = QString(QCryptographicHash::hash((line),QCryptographicHash::Sha1).toHex());
            break;
        }

        if (hash==this->hashWatku) {
            mutex.lock();
            QTime time = QTime::currentTime();
            QString timeString = time.toString();
            emit NumberChanged(line);
            this->Stop = true;
            mutex.unlock();
            file.close();

            emit ZmienionoPasek();
            break;
           // return;
        }
       // ui->logiEdit->appendPlainText("Number");
        //emit NumberChanged(line);


       // this->msleep(1);
        if (licznik>=10000) {
            licznik=0;
            emit ZmienionoPasek();
        }
    }
   // mutex.unlock();
    emit Koniec();

}

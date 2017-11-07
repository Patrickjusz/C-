#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QString>

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = 0);
    void run();
    bool Stop;
    int hashJaki;
    QString hashWatku;

signals:
    void NumberChanged(QString);
    void ZmienionoPasek();
    void Koniec();


public slots:

};

#endif // MYTHREAD_H

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QString>
#include <QPushButton>
#include <QTime>
#include <plik.h>
#include <QCryptographicHash>
#include <QFile>
#include <QFont>
#include <QApplication>
#include <QSound>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mThread = new MyThread(this);
    connect(mThread, SIGNAL(NumberChanged(QString)), this, SLOT(onNumberChanged(QString)));
    connect(mThread, SIGNAL(ZmienionoPasek()), this, SLOT(onZmienionoPasek()));
    connect(mThread, SIGNAL(Koniec()), this, SLOT(onKoniec()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onNumberChanged(QString Number) {
    QTime time = QTime::currentTime();
    QString timeString = time.toString();
    ui->logiEdit->appendPlainText(QString("[").append(timeString).append("] Znaleziono skrót ").append(ui->comboBox->currentText()).append(": ").append(Number));
    if (ui->checkBox->isChecked())
        QSound::play("C:\\Users\\Patryk\\Downloads\\gotowe.wav");

    ui->progressBar->setValue(ui->progressBar->maximum());
}

void MainWindow::onZmienionoPasek() {
    ui->progressBar->setValue(ui->progressBar->value()+1);
}

void MainWindow::onKoniec() {
    ui->pushButton->setEnabled(1);
    ui->comboBox->setEnabled(1);
    ui->hashEdit->setEnabled(1);
    ui->slownikEdit->setEnabled(1);
    ui->progressBar->setValue(ui->progressBar->maximum());
    if (ui->checkBox->isChecked())
        QSound::play("C:\\Users\\Patryk\\Downloads\\end.wav");
}

void MainWindow::on_pushButton_clicked()
{
    QString nazwaPliku = QFileDialog::getOpenFileName(this, tr("Otwórz słownik"), "slownik.txt", tr("Plik tekstowy (*.txt *.dic *.dat)"));
    ui->slownikEdit->setText(nazwaPliku);
    QTime time = QTime::currentTime();
    QString timeString = time.toString();
    QString logiAkcja = "[";
    logiAkcja.append(timeString);
    logiAkcja.append("] Załadowano słownik: ");
    logiAkcja.append(nazwaPliku);
    ui->logiEdit->appendPlainText(logiAkcja);
}

void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    QTime time = QTime::currentTime();
    QString timeString = time.toString();
    QString logiAkcja = "[";
    QString typKodowania = ui->comboBox->currentText();
    logiAkcja.append(timeString);
    logiAkcja.append("] Zmieniono typ hashu na ");
    logiAkcja.append(typKodowania);
    ui->logiEdit->appendPlainText(logiAkcja);
}

void MainWindow::on_pushButton_2_clicked()
{
    QFile file(ui->slownikEdit->text());

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QString hash;
    while (!file.atEnd()) {
        QByteArray line = file.readLine().simplified();
        hash = QString(QCryptographicHash::hash((line),QCryptographicHash::Md5).toHex());
        if (hash==ui->hashEdit->text()) {
            QTime time = QTime::currentTime();
            QString timeString = time.toString();
            ui->logiEdit->appendPlainText(QString("[").append(timeString).append("] Znaleziono: ").append(line));
            return;
        }

    }
    QTime time = QTime::currentTime();
    QString timeString = time.toString();
    ui->logiEdit->appendPlainText(QString("[").append(timeString).append("] Nie znaleziono w słowniku!"));
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->pushButton->setEnabled(0);
    ui->comboBox->setEnabled(0);
    ui->hashEdit->setEnabled(0);
    ui->slownikEdit->setEnabled(0);
    QFile file(ui->slownikEdit->text());

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QByteArray line;
    long long licznik=0;

    while (!file.atEnd()) {
        line = file.readLine();
        licznik=licznik+1;
    }
    QTime time = QTime::currentTime();
    QString timeString = time.toString();
    ui->logiEdit->appendPlainText(QString("[").append(timeString).append("] Słownik posiada ").append(QString::number(licznik)).append(" potencjalnych haseł."));
    licznik=licznik/10000+1;
    ui->progressBar->setMinimum(0);
    ui->progressBar->setValue(0);
    ui->progressBar->setMaximum(licznik);
    mThread->hashWatku = ui->hashEdit->text();
    mThread->hashJaki = ui->comboBox->currentIndex();
    mThread->start();
    time = QTime::currentTime();
    timeString = time.toString();

    ui->logiEdit->appendPlainText(QString("[").append(timeString).append("] Rozpoczęto łamanie hashu!"));
}

void MainWindow::on_pushButton_5_clicked()
{
    //stop
    mThread->Stop = true;
}

void MainWindow::on_pushButton_6_clicked()
{
    mThread->run();
}

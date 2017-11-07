#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "plik.h"
#include <QFileDialog>
#include <QString>
#include <QPushButton>
#include <QTime>
Plik::Plik()
{
}

bool Plik::zaladujPlik() {
    QString nazwaPliku = QFileDialog::getOpenFileName(this, tr("Otwórz słownik"), "slownik.txt", tr("Plik tekstowy (*.txt *.dic *.dat)"));
    ui->slownikEdit->setText(nazwaPliku);
    QTime time = QTime::currentTime();
    QString timeString = time.toString();
    QString logiAkcja = timeString;
    logiAkcja.append(" Załadowano słownik: ");
    logiAkcja.append(nazwaPliku);
    ui->logiEdit->appendPlainText(logiAkcja);
    return 1;
}

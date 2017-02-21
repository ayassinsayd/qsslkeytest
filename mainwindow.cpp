#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QDebug>
#include <QSslKey>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->closeButton,SIGNAL(clicked(bool)),this,SLOT(close()));

    QString fileName(":/keys/key_encrypted.key");

    QFile f(fileName);
    if ( f.open(QIODevice::ReadOnly) ) {
        QByteArray arr = f.readAll();

        QSslKey key(arr, QSsl::Rsa,QSsl::Pem,QSsl::PrivateKey,"f7um1oCYN+3Mtc0PHrnckA==");
        qDebug()<<"Encrypted key isNull:"<<key.isNull();
        ui->encryptedStatus->setText(QString("Encrypted key %1").arg(key.isNull() ? QString("is NULL") : QString("OK")));
    } else
        ui->encryptedStatus->setText(QString("Cant read key file:%1").arg(fileName));

    fileName=":/keys/key_decrypted.key";
    QFile f2(fileName);
    if ( f2.open(QIODevice::ReadOnly) ) {
        QByteArray arr = f2.readAll();

        QSslKey key(arr, QSsl::Rsa,QSsl::Pem,QSsl::PrivateKey);
        qDebug()<<"Decrypted key isNull:"<<key.isNull();
        ui->decryptedStatus->setText(QString("Decrypted key %1").arg(key.isNull() ? QString("is NULL") : QString("OK")));
    } else
        ui->decryptedStatus->setText(QString("Cant read key file:%1").arg(fileName));
}

MainWindow::~MainWindow()
{
    delete ui;
}

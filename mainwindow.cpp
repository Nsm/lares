#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindowClass)
{
    ui->setupUi(this);
    connection = new AresConnection();
    ui->statusBar->addWidget(statusMessage = new QLabel(this));
    connect(connection,SIGNAL(statusChanged(AresConnection::Status )),this,SLOT(connectionStatusChanged(AresConnection::Status)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    connection->open();
}

void MainWindow::connectionStatusChanged(AresConnection::Status newStatus){
    switch(newStatus){
        case AresConnection::CONNECT:
            statusMessage->setText("Conectado");
        break;
        case AresConnection::CONNECTING:
            statusMessage->setText("Conectando..");
        break;
        case AresConnection::DISCONNECTED:
            statusMessage->setText("Desconectado");
        break;
    }
}

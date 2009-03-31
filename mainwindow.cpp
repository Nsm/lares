#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindowClass)
{
    ui->setupUi(this);
    connection = new AresConnection();
    ui->statusBar->addWidget(statusMessage = new QLabel(this));

    searchWidget = new AresSearchWidget();
    ui->tabSearch->layout()->addWidget(searchWidget);
    searchWidget->setVisible(true);

    connect(connection,SIGNAL(statusChanged(AresConnection::Status )),this,SLOT(connectionStatusChanged(AresConnection::Status)));
    connect(connection,SIGNAL(itemFinded(AresItem *, int)),this,SLOT(itemFinded(AresItem * , int )));
}

MainWindow::~MainWindow()
{
    delete ui;
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

void MainWindow::on_leSearch_returnPressed()
{
    searchWidget->addSearch(connection->search(ui->leSearch->text()),ui->leSearch->text());
    ui->statusBar->showMessage(tr("Buscando "));
}

void MainWindow::itemFinded(AresItem * item, int searchId){
    searchWidget->addItem(item,searchId);
}

void MainWindow::on_pbConnect_clicked()
{
    connection->open();
}

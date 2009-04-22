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

    downloadWidget = new AresDownloadWidget();
    ui->tabDownload->layout()->addWidget(downloadWidget);
    downloadWidget->setVisible(true);

    connect(connection,SIGNAL(statusChanged(AresConnection::Status )),this,SLOT(connectionStatusChanged(AresConnection::Status)));
    connect(connection,SIGNAL(itemFinded(AresItem *, int)),this,SLOT(itemFinded(AresItem * , int )));
    connect(searchWidget,SIGNAL(downloadRequested(AresDownloadRequest*)),this,SLOT(startDownload(AresDownloadRequest *)));
    connect(connection,SIGNAL(downloadStarted(AresDownload*)),this,SLOT(downloadStarted(AresDownload*)));
    connect(connection,SIGNAL(downloadChanged(AresDownload*)),downloadWidget,SLOT(updateDownload(AresDownload*)));
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
    connection->search(ui->leSearch->text());
    searchWidget->clear();
    ui->statusBar->showMessage(tr("Buscando %1").arg(ui->leSearch->text()),2000);
}

void MainWindow::itemFinded(AresItem * item, int searchId){
    searchWidget->addItem(item);
}

void MainWindow::on_pbConnect_clicked()
{
    connection->open();
}

void MainWindow::startDownload(AresDownloadRequest * download){
    ui->statusBar->showMessage(tr("Descargando %1 ").arg(download->getFileName()),2000);
    connection->download(download);
    delete download;
}

void MainWindow::downloadStarted(AresDownload * download){
    downloadWidget->addDownload(download);
}

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindowClass)
{
    ui->setupUi(this);
    connection = new AresConnection();
    ui->statusBar->addWidget(statusMessage = new QLabel(this));

    tabSearchResult = new QTabWidget();
    ui->tabSearch->layout()->addWidget(tabSearchResult);

    tabSearchResult->setVisible(true);

    downloadWidget = new AresDownloadWidget();
    ui->tabDownload->layout()->addWidget(downloadWidget);
    downloadWidget->setVisible(true);

    connect(connection,SIGNAL(statusChanged(AresConnection::Status )),this,SLOT(connectionStatusChanged(AresConnection::Status)));
    connect(connection,SIGNAL(itemFinded(AresItem *, int)),this,SLOT(itemFinded(AresItem * , int )));
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
    //se crea una nueva busqueda y un nuevo tab para mostrarla
    int searchId = connection->search(ui->leSearch->text());

    AresSearchWidget * searchWidget = new AresSearchWidget();
    tabSearchResult->addTab(searchWidget,ui->leSearch->text());
    searchWidget->setVisible(true);
    //se conecta la señal del widget de busqueda de iniciar una nueva descarga con el slot correspondiente
    connect(searchWidget,SIGNAL(downloadRequested(AresDownloadRequest*)),this,SLOT(startDownload(AresDownloadRequest *)));
    searchWidgets.insert(searchId,searchWidget);
    ui->statusBar->showMessage(tr("Buscando %1").arg(ui->leSearch->text()),2000);
}

void MainWindow::itemFinded(AresItem * item, int searchId){
    searchWidgets[searchId]->addItem(item);
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

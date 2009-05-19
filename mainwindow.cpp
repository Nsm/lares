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
    tabSearchResult->setTabsClosable(true);
    tabSearchResult->setVisible(true);

    downloadWidget = new AresDownloadWidget();
    ui->tabDownload->layout()->addWidget(downloadWidget);
    downloadWidget->setVisible(true);
    connect(tabSearchResult,SIGNAL(currentChanged(int)),this,SLOT(currentSearchTabChanged(int)));
    connect(tabSearchResult,SIGNAL(tabCloseRequested(int)),this,SLOT(closeSearchTab(int)));
    connect(connection,SIGNAL(statusChanged(AresConnection::Status )),this,SLOT(connectionStatusChanged(AresConnection::Status)));
    connect(connection,SIGNAL(itemFinded(AresItem *, int)),this,SLOT(itemFinded(AresItem * , int )));
    connect(connection,SIGNAL(downloadStarted(AresDownload*)),this,SLOT(downloadStarted(AresDownload*)));
    connect(connection,SIGNAL(downloadChanged(int)),downloadWidget,SLOT(updateDownload(int)));
    connect(connection,SIGNAL(downloadCancelled(int)),downloadWidget,SLOT(removeDownload(int)));
    connect(downloadWidget,SIGNAL(downloadCancelled(int)),connection,SLOT(cancelDownload(int)));
    connect(downloadWidget,SIGNAL(downloadPaused(int)),connection,SLOT(pauseDownload(int)));
    connect(downloadWidget,SIGNAL(downloadResumed(int)),connection,SLOT(unpauseDownload(int)));
    connect(downloadWidget,SIGNAL(downloadRemoved(int)),connection,SLOT(deleteDownload(int)));
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

void MainWindow::currentSearchTabChanged(int tabId){
    AresSearchWidget * searchWidget = (AresSearchWidget *) tabSearchResult->widget(tabId);
    if(searchWidget->isCancelled()){
        ui->pbStopSearch->setEnabled(false);
    }else{
        ui->pbStopSearch->setEnabled(true);
    }
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

void MainWindow::closeSearchTab(int tabId){
    AresSearchWidget * searchWidget = (AresSearchWidget *) tabSearchResult->widget(tabId);
    int searchId = searchWidget->getSearchId();
    searchWidgets.remove(searchId);
    tabSearchResult->removeTab(tabId);
    delete searchWidget;
    connection->cancelSearch(searchId);
}

void MainWindow::on_pbSearch_clicked()
{
     //se crea una nueva busqueda y un nuevo tab para mostrarla
    int searchId = connection->search(ui->leSearch->text());

    AresSearchWidget * searchWidget = new AresSearchWidget();
    searchWidget->setSearchId(searchId);
    tabSearchResult->addTab(searchWidget,ui->leSearch->text());
    searchWidget->setVisible(true);
    //se conecta la señal del widget de busqueda de iniciar una nueva descarga con el slot correspondiente
    connect(searchWidget,SIGNAL(downloadRequested(AresDownloadRequest*)),this,SLOT(startDownload(AresDownloadRequest *)));
    searchWidgets.insert(searchId,searchWidget);
    ui->statusBar->showMessage(tr("Buscando %1").arg(ui->leSearch->text()),2000);
}

void MainWindow::on_pbStopSearch_clicked()
{
    AresSearchWidget * searchWidget = (AresSearchWidget *) tabSearchResult->currentWidget();
    if(!searchWidget->isCancelled()){
        ui->pbStopSearch->setEnabled(false);
        searchWidget->setCancelled(true);
        connection->cancelSearch(searchWidget->getSearchId());
    }
}

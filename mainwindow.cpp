#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindowClass)
{
    ui->setupUi(this);

    //se inicializan los elementos necesarios para realizar vistas previas de canciones y videos
    mediaPreview = NULL;
    seekSlider = new Phonon::SeekSlider();
    ui->previewControlsLayout->addWidget(seekSlider);

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
    connect(downloadWidget,SIGNAL(downloadPreviewed(int)),this,SLOT(previewDownload(int)));
    connect(downloadWidget,SIGNAL(sourcesFinded(int)),connection,SLOT(findSources(int)));
}

MainWindow::~MainWindow()
{
    connection->close();
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
    if(tabId >= 0){
        AresSearchWidget * searchWidget = (AresSearchWidget *) tabSearchResult->widget(tabId);
        if(searchWidget->isSearchCancelled()){
            ui->pbStopSearch->setEnabled(false);
        }else{
            ui->pbStopSearch->setEnabled(true);
        }
    }
}

void MainWindow::itemFinded(AresItem * item, int searchId){
    if(searchWidgets.contains(searchId)){
        searchWidgets[searchId]->addItem(item);
    }
}

void MainWindow::on_pbConnect_clicked()
{
    connection->open();
    ui->pbDisconnect->setEnabled(true);
    ui->pbConnect->setEnabled(false);
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
    tabSearchResult->removeTab(tabId);
    searchWidgets.remove(searchId);
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
    if(!searchWidget->isSearchCancelled()){
        ui->pbStopSearch->setEnabled(false);
        searchWidget->setSearchCancelled(true);
        connection->cancelSearch(searchWidget->getSearchId());
    }
}

void MainWindow::previewDownload(int downloadId){
    AresDownload * download = connection->getDownload(downloadId);
    if(mediaPreview != NULL){
        mediaPreview->stop();
        delete mediaPreview;
    }
    mediaPreview = Phonon::createPlayer(Phonon::MusicCategory,Phonon::MediaSource(download->getFilePath()));
    seekSlider->setMediaObject(mediaPreview);
    mediaPreview->play();
    ui->statusBar->showMessage(tr("Previsualizando %1").arg(download->getFileName()),2000);
    ui->statusBar->showMessage(download->getFilePath(),2000);
}

void MainWindow::on_tbPreviewPlay_clicked()
{
    if(mediaPreview){
        mediaPreview->play();
    }
}

void MainWindow::on_tbPreviewPause_clicked()
{
    if(mediaPreview){
        mediaPreview->pause();
    }
}

void MainWindow::on_tbPreviewStop_clicked()
{
    if(mediaPreview){
        mediaPreview->stop();
    }
}

void MainWindow::on_pbDisconnect_clicked()
{
    connection->close();
    ui->pbDisconnect->setEnabled(false);
    ui->pbConnect->setEnabled(true);
}

#include "aresdownloadwidget.h"
#include "ui_aresdownloadwidget.h"

AresDownloadWidget::AresDownloadWidget(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::AresDownloadWidget)
{
    m_ui->setupUi(this);
    m_ui->twDownloads->setItemDelegate(new AresDownloadWidgetDelegate());
    m_ui->twDownloads->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_ui->twDownloads,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(showContextMenu(QPoint)));
}

AresDownloadWidget::~AresDownloadWidget()
{
    delete m_ui;
}

void AresDownloadWidget::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void AresDownloadWidget::addDownload(AresDownload *download){
    AresDownloadWidgetItem * newItem = new AresDownloadWidgetItem(m_ui->twDownloads,download);
    itemsHash.insert(download->getId(),newItem);
}

void AresDownloadWidget::updateDownload(int downloadId){
    if(itemsHash.contains(downloadId)){
        AresDownloadWidgetItem * itemToUpdate = itemsHash[downloadId];
        itemToUpdate->update();
    }
}

void AresDownloadWidget::removeDownload(int downloadId){
    if(itemsHash.contains(downloadId)){
        AresDownloadWidgetItem * itemToRemove = itemsHash[downloadId];
        itemsHash.remove(downloadId);
        delete itemToRemove;
        emit downloadRemoved(downloadId);
    }
}

void AresDownloadWidget::showContextMenu( const QPoint & pos ){
    QMenu * contextMenu = new QMenu();
    AresDownloadWidgetItem * item = (AresDownloadWidgetItem *)m_ui->twDownloads->itemAt(pos);
    if(item){
        AresDownload::State itemState = item->getDownloadState();
        //Las acciones del menu contextual se muestran de acuerdo al estado del item sobre el cual se ejecutaran (el que este bajo el raton)
        contextMenu->addAction(m_ui->actionPreview);
        if( itemState == AresDownload::ACTIVE){
            contextMenu->addAction(m_ui->actionPause);
        }else if(itemState == AresDownload::PAUSED){
            contextMenu->addAction(m_ui->actionResume);
        }
        if(itemState != AresDownload::COMPLETED){
            contextMenu->addAction(m_ui->actionFindSources);
            contextMenu->addAction(m_ui->actionCancel);
        }else{
            contextMenu->addAction(m_ui->actionRemove);
        }
        contextMenu->addSeparator();
    }
    //acciones que se muestran siempre:
    contextMenu->addAction(m_ui->actionRemoveAll);
    contextMenu->exec(QCursor::pos());
}

void AresDownloadWidget::on_actionCancel_triggered()
{
    AresDownloadWidgetItem * item = (AresDownloadWidgetItem *)m_ui->twDownloads->currentItem();
    int downloadId = item->getDownloadId();
    emit downloadCancelled(downloadId);
}

void AresDownloadWidget::on_actionPause_triggered()
{
    AresDownloadWidgetItem * item = (AresDownloadWidgetItem *)m_ui->twDownloads->currentItem();
    int downloadId = item->getDownloadId();
    item->setDownloadState(AresDownload::PAUSED);
    emit downloadPaused(downloadId);
}

void AresDownloadWidget::on_actionResume_triggered()
{
    AresDownloadWidgetItem * item = (AresDownloadWidgetItem *)m_ui->twDownloads->currentItem();
    int downloadId = item->getDownloadId();
    item->setDownloadState(AresDownload::ACTIVE);
    emit downloadResumed(downloadId);
}

void AresDownloadWidget::on_actionRemove_triggered()
{
    AresDownloadWidgetItem * item = (AresDownloadWidgetItem *)m_ui->twDownloads->currentItem();
    int downloadId = item->getDownloadId();
    removeDownload(downloadId);
}

/*
  Quita de la lista todos los items que ya se han completado
*/
void AresDownloadWidget::on_actionRemoveAll_triggered()
{
    foreach(AresDownloadWidgetItem * item, itemsHash){
        if(item->getDownloadState() == AresDownload::COMPLETED){
            removeDownload(item->getDownloadId());
        }
    }
}

void AresDownloadWidget::on_actionPreview_triggered()
{
    AresDownloadWidgetItem * item = (AresDownloadWidgetItem *)m_ui->twDownloads->currentItem();
    emit downloadPreviewed(item->getDownloadId());
}

void AresDownloadWidget::on_actionFindSources_triggered()
{
    AresDownloadWidgetItem * item = (AresDownloadWidgetItem *)m_ui->twDownloads->currentItem();
    emit sourcesFinded(item->getDownloadId());
}

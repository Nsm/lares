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
        delete itemToRemove;
        emit downloadRemoved(downloadId);
    }
}

void AresDownloadWidget::showContextMenu( const QPoint & pos ){
    AresDownloadWidgetItem * item = (AresDownloadWidgetItem *)m_ui->twDownloads->itemAt(pos);
    if(item){
        QMenu * contextMenu = new QMenu();
        contextMenu->addAction(m_ui->actionCancel);
        if(item->getDownloadState() == AresDownload::ACTIVE){
            contextMenu->addAction(m_ui->actionPause);
        }else if(item->getDownloadState() == AresDownload::PAUSED){
            contextMenu->addAction(m_ui->actionResume);
        }
        contextMenu->exec(QCursor::pos());
    }
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

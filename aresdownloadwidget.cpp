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
    AresDownloadWidgetItem * newItem = new AresDownloadWidgetItem(m_ui->twDownloads);
    newItem->setDownloadId(download->getId());
    newItem->setText(0,download->getFileName());
    newItem->setText(1,QString::number(qRound(download->getSize() / 1024)) + "Kb");
    newItem->setText(2,QString::number(qRound(download->getTransmit() / 1024)) + "Kb");
    int percentage = 100;
    if(download->getSize()){
        percentage = download->getTransmit() * 100 / download->getSize();
    }
    newItem->setData(3,Qt::DisplayRole, percentage);
    itemsHash.insert(download->getId(),newItem);
}

void AresDownloadWidget::updateDownload(AresDownload *download){
    if(itemsHash.contains(download->getId())){
        AresDownloadWidgetItem * itemToUpdate = itemsHash[download->getId()];
        itemToUpdate->setText(2,QString::number(qRound(download->getTransmit() / 1024)) + "Kb");
        int percentage = 100;
        if(download->getSize()){
            percentage = download->getTransmit() * 100 / download->getSize();
        }
        itemToUpdate->setData(3,Qt::DisplayRole, percentage);
    }
}

void AresDownloadWidget::showContextMenu( const QPoint & pos ){
    AresDownloadWidgetItem * item = (AresDownloadWidgetItem *)m_ui->twDownloads->itemAt(pos);
    if(item){
        QMenu * contextMenu = new QMenu();
        contextMenu->addAction(m_ui->actionCancel);
        contextMenu->exec(QCursor::pos());
    }
}

void AresDownloadWidget::on_actionCancel_triggered()
{
    AresDownloadWidgetItem * item = (AresDownloadWidgetItem *)m_ui->twDownloads->currentItem();
    int downloadId = item->getDownloadId();
    emit downloadCancelled(downloadId);
}

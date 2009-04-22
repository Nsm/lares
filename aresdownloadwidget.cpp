#include "aresdownloadwidget.h"
#include "ui_aresdownloadwidget.h"

AresDownloadWidget::AresDownloadWidget(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::AresDownloadWidget)
{
    m_ui->setupUi(this);
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
    QTreeWidgetItem * newItem = new QTreeWidgetItem(m_ui->twDownloads);
    newItem->setText(0,download->getFileName());
    newItem->setText(1,QString::number(qRound(download->getSize() / 1024)) + "Kb");
    newItem->setText(2,QString::number(qRound(download->getTransmit() / 1024)) + "Kb");
    newItem->setText(3,QString::number(download->getTransmit() * 100 / download->getSize()) + "%");
    itemsHash.insert(download->getId(),newItem);
}

void AresDownloadWidget::updateDownload(AresDownload *download){
    if(itemsHash.contains(download->getId())){
        QTreeWidgetItem * itemToUpdate = itemsHash[download->getId()];
        itemToUpdate->setText(2,QString::number(qRound(download->getTransmit() / 1024)) + "Kb");
        itemToUpdate->setText(3,QString::number(download->getTransmit() * 100 / download->getSize()) + "%");
    }
}

#include "aresdownloadwidgetitem.h"

AresDownloadWidgetItem::AresDownloadWidgetItem(QTreeWidget * parent,AresDownload * download):
        QTreeWidgetItem(parent)
{
    this->download = download;
    //se muestra la informacion fija del item
    this->setText(0,download->getFileName());
    this->setText(1,QString::number(qRound(download->getSize() / 1024)) + "Kb");
    //se muestra la informacion que varia con el tiempo del item
    this->update();
}

int AresDownloadWidgetItem::getDownloadId()
{
    return download->getId();
}

/*
  Actualiza la informacion variable del item obteniendo los datos del objeto download
*/
void AresDownloadWidgetItem::update()
{
    this->setText(2,QString::number(qRound(download->getTransmit() / 1024)) + "Kb");
    int percentage = 100;
    if(download->getSize()){
        percentage = download->getTransmit() * 100 / download->getSize();
    }
    this->setData(3,Qt::DisplayRole, percentage);

    //dependiendo del estado de la descarga se utiliza un color para la fuente
    QBrush brush;
    switch(download->getState()){
        case AresDownload::COMPLETED:
            brush.setColor(QColor::fromRgb(0,255,0));
        break;
        case AresDownload::PAUSED:
            brush.setColor(QColor::fromRgb(0,0,255));
        break;
        case AresDownload::ACTIVE:
            brush.setColor(QColor::fromRgb(0,0,0));
        break;
    }
    for(int i = 0; i < this->columnCount();i++ ){
        this->setForeground(i,brush);
    }
}

AresDownload::State AresDownloadWidgetItem::getDownloadState(){
    return download->getState();
}

#include "aresdownloadwidgetitem.h"

AresDownloadWidgetItem::AresDownloadWidgetItem(QTreeWidget * parent,AresDownload * download):
        QTreeWidgetItem(parent)
{
    this->download = download;
    //se muestra la informacion fija del item
    this->setText(NAME,download->getFileName());
    this->setText(SIZE,QString::number(qRound(download->getSize() / 1024)) + "Kb");
    //se pone en el rol de usuario el valor numerico completo del tamaño para poder usarlo cuando se ordena la lista
    this->setData(SIZE,Qt::UserRole,int(download->getSize()));
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
    this->setText(DOWNLOADED,QString::number(qRound(download->getTransmit() / 1024)) + "Kb");
    //se pone en el rol de usuario el valor numerico completo del tamaño de la descarga para poder usarlo cuando se ordena la lista
    this->setData(DOWNLOADED,Qt::UserRole,int(download->getTransmit()));
    int percentage = 100;
    if(download->getSize()){
        percentage = download->getTransmit() * 100 / download->getSize();
    }
    this->setData(PERCENTAGE,Qt::DisplayRole, percentage);
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

void AresDownloadWidgetItem::setDownloadState(AresDownload::State state){
    download->setState(state);
    //actualiza el item (informacion mostrada, color, etc)
    update();
}

bool AresDownloadWidgetItem::operator<(const QTreeWidgetItem &other)const{
    int column = treeWidget()->sortColumn();
    if( column == PERCENTAGE ){
        return data(column,Qt::DisplayRole).toInt() < other.data(column,Qt::DisplayRole).toInt();
    }else if(column == SIZE || column == DOWNLOADED){
        return data(column,Qt::UserRole).toInt() < other.data(column,Qt::UserRole).toInt();
    }else{
        return QTreeWidgetItem::operator <(other);
    }
}

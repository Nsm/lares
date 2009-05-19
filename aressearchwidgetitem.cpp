#include "aressearchwidgetitem.h"

AresSearchWidgetItem::AresSearchWidgetItem(QTreeWidget * parent):
        QTreeWidgetItem(parent)
{

}

AresSearchWidgetItem::~AresSearchWidgetItem(){

}

void AresSearchWidgetItem::addAresItem(AresItem * item){
    if(!aresItems.count()){
        /*
        * si la lista de items de ares esta vacia entonces se llena la informacion
        * del elemento del listado con los datos de este primer item
        */
        this->setText(0,item->getFileName());
        this->setText(1,QString::number(qRound(item->getSize() / 1024)) + " Kb");
    }

    aresItems.append(item);

    //se actualiza la cantidad de fuentes del elemento del listado
    this->setText(2,QString::number(aresItems.count()));
}

AresDownloadRequest * AresSearchWidgetItem::getDownloadRequest(){    
    if(aresItems.isEmpty()){
        //si no hay items atachados a este elemento entonces no se puede generar un request
        return NULL;
    }
    AresDownloadRequest * request = new AresDownloadRequest();
    //el nombre del archivo se saca del primer item,
    //el hash y el tamaño tambien porque se supone que son iguales para todas las fuentes de un mismo archivo
    request->setFileName(aresItems[0]->getFileName());
    request->setHash(aresItems[0]->getHash());
    request->setSize(aresItems[0]->getSize());
    foreach(AresItem * item, aresItems ){
        request->addSource(item->getUser(),item->getUrl());
    }
    return request;
}

bool AresSearchWidgetItem::operator<(const QTreeWidgetItem &other)const{
    int column = treeWidget()->sortColumn();
    if( column == 2){
        return data(column,Qt::DisplayRole).toInt() < other.data(column,Qt::DisplayRole).toInt();
    }else{
        return QTreeWidgetItem::operator <(other);
    }
}

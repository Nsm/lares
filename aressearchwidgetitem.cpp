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
        this->setText(1,QString::number(qRound(item->getSize() / 1000)) + " Kb");
    }

    aresItems.append(item);

    //se actualiza la cantidad de fuentes del elemento del listado
    this->setText(2,QString::number(aresItems.count()));
}

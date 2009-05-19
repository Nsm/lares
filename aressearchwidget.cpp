#include "aressearchwidget.h"
#include "ui_aressearchwidget.h"

AresSearchWidget::AresSearchWidget(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::AresSearchWidget)
{
    m_ui->setupUi(this);
    cancelled = false;
}

AresSearchWidget::~AresSearchWidget()
{
    delete m_ui;
}

int AresSearchWidget::getSearchId(){
    return searchId;
}

void AresSearchWidget::setSearchId(int searchId){
    this->searchId = searchId;
}

bool AresSearchWidget::isCancelled(){
    return cancelled;
}

void AresSearchWidget::setCancelled(bool cancelled){
    this->cancelled = cancelled;
}

void AresSearchWidget::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void AresSearchWidget::addItem(AresItem * item){
    if(! itemsHash.contains(item->getHash()) ){
        itemsHash[item->getHash()] = new AresSearchWidgetItem(m_ui->twSearch);
    }
    itemsHash[item->getHash()]->addAresItem(item);
}

void AresSearchWidget::clear(){
    m_ui->twSearch->clear();
}

void AresSearchWidget::on_twSearch_itemDoubleClicked(QTreeWidgetItem* item, int column)
{
    AresSearchWidgetItem * clickedItem = (AresSearchWidgetItem * ) item;
    emit downloadRequested(clickedItem->getDownloadRequest());
}

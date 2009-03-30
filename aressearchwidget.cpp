#include "aressearchwidget.h"
#include "ui_aressearchwidget.h"

AresSearchWidget::AresSearchWidget(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::AresSearchWidget)
{
    m_ui->setupUi(this);
}

AresSearchWidget::~AresSearchWidget()
{
    delete m_ui;
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
    QTreeWidgetItem * newItem = new QTreeWidgetItem(m_ui->twSearch);
    newItem->setText(0,item->getFileName());
    newItem->setText(1,QString::number(item->getSize()));
    newItem->setText(2,"1");
    //TODO
}

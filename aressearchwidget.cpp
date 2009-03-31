#include "aressearchwidget.h"
#include "ui_aressearchwidget.h"

AresSearchWidget::AresSearchWidget(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::AresSearchWidget)
{
    m_ui->setupUi(this);
    tabSearch = new QTabWidget();
    tabSearch->setVisible(true);
    layout()->addWidget(tabSearch);
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

void AresSearchWidget::addItem(AresItem * item, int searchId){

    //TODO
}

void AresSearchWidget::addSearch(int searchId,QString searchTitle){
    tabSearch->addTab(new QTreeWidget(),searchTitle);
}

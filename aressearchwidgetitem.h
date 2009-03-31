#ifndef ARESSEARCHWIDGETITEM_H
#define ARESSEARCHWIDGETITEM_H

#include <QTreeWidgetItem>
#include <QList>
#include "aresitem.h"
class AresSearchWidgetItem : public QTreeWidgetItem
{
public:
    AresSearchWidgetItem(QTreeWidget * parent);
    virtual ~AresSearchWidgetItem();
    void addAresItem(AresItem * item);
private:
    QList<AresItem *> aresItems;
};

#endif // ARESSEARCHWIDGETITEM_H

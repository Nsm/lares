#ifndef ARESSEARCHWIDGETITEM_H
#define ARESSEARCHWIDGETITEM_H

#include <QTreeWidgetItem>
#include <QList>
#include "aresitem.h"
#include "aresdownloadrequest.h"
class AresSearchWidgetItem : public QTreeWidgetItem
{
public:
    AresSearchWidgetItem(QTreeWidget * parent);
    virtual ~AresSearchWidgetItem();
    void addAresItem(AresItem * item);
    AresDownloadRequest * getDownloadRequest();
private:
    QList<AresItem *> aresItems;
};

#endif // ARESSEARCHWIDGETITEM_H

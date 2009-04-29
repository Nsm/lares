#ifndef ARESDOWNLOADWIDGETITEM_H
#define ARESDOWNLOADWIDGETITEM_H

#include <QTreeWidgetItem>

class AresDownloadWidgetItem : public QTreeWidgetItem
{
public:
    AresDownloadWidgetItem();
    inline AresDownloadWidgetItem(QTreeWidget * parent): QTreeWidgetItem(parent){}
    inline int getDownloadId(){ return downloadId; }
    void setDownloadId(int id){downloadId = id;}
private:
    int downloadId;
};

#endif // ARESDOWNLOADWIDGETITEM_H

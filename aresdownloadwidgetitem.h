#ifndef ARESDOWNLOADWIDGETITEM_H
#define ARESDOWNLOADWIDGETITEM_H

#include <QTreeWidgetItem>
#include "aresdownload.h"
class AresDownloadWidgetItem : public QTreeWidgetItem
{
public:
    static const int NAME = 0, SIZE = 1, DOWNLOADED = 2, PERCENTAGE = 3;
    AresDownloadWidgetItem();
    AresDownloadWidgetItem(QTreeWidget * parent,AresDownload * download);
    int getDownloadId();
    AresDownload::State getDownloadState();
    void setDownloadState(AresDownload::State state);
    //actualiza la informacion mostrada en el item utilizando la informacion de la descarga(del objeto download)
    void update();
private:
    AresDownload * download;
    bool operator<(const QTreeWidgetItem &other)const;
};

#endif // ARESDOWNLOADWIDGETITEM_H

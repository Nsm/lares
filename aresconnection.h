#ifndef ARESCONNECTION_H
#define ARESCONNECTION_H

#include <QObject>
#include "stdio.h"
#include "giftconnection.h"
#include "aresitem.h"
#include "aresdownloadrequest.h"
#include "aresdownload.h"

class AresConnection : public QObject
{
    Q_OBJECT
public:
    AresConnection();
    enum Status{CONNECT, CONNECTING, DISCONNECTED};
    void open();
    void close();
    int search(QString query);
    void download(AresDownloadRequest *request);
    AresDownload * getDownload(int downloadId);
public slots:
    void cancelSearch(int searchId);
    void cancelDownload(int downloadId);
    void pauseDownload(int downloadId);
    void unpauseDownload(int downloadId);
    //elimina una desacarga y su informacion asociada
    void deleteDownload(int downloadId);
    void findSources(int downloadId);
private:
    GIftConnection * giftConnection;
    Status connectionStatus;
    void setStatus(Status status);
    Status getStatus();
    void newSearchedItem(GIftCommand * command);
    void newDownload(GIftCommand * command);
    void updateDownload(GIftCommand * command);
    void downloadFinished(int downloadId);
    void addSource(int downloadId, QString url, QString user);
    //lista (hash) de descargas actuales:
    QHash<int,AresDownload *> downloads;
    //hash que relaciona las descargas con su codigo unico (hash del protocolo gft) y pemite una busqueda rapida
    QHash<QString, AresDownload *> downloadHash;
    //relacion entre busqueda de fuentes y descargas a las que pertenecen
    QHash<int,int> sourceLocateDownloads;
private slots:
    void readCommand();
signals:
    void statusChanged(AresConnection::Status newStatus);
    void itemFinded(AresItem * item, int searchId);
    void searchFinished(int searchId);
    void downloadStarted(AresDownload * download);
    void downloadChanged(int downloadId);
    void downloadCompleted(int downloadId);
    void downloadCancelled(int downloadId);
};

#endif // ARESCONNECTION_H

#ifndef ARESCONNECTION_H
#define ARESCONNECTION_H

#include <QObject>
#include "giftconnection.h"
#include "aresitem.h"
#include "aresdownloadrequest.h"

class AresConnection : public QObject
{
    Q_OBJECT
public:
    AresConnection();
    enum Status{CONNECT, CONNECTING, DISCONNECTED};
    void open();
    void close();
    int search(QString query);
    void download(AresDownloadRequest request);

private:
    GIftConnection * giftConnection;
    Status connectionStatus;
    void setStatus(Status status);
    Status getStatus();
private slots:
    void readCommand();
signals:
    void statusChanged(AresConnection::Status newStatus);
    void itemFinded(AresItem * item, int searchId);
    void searchFinished(int searchId);
};

#endif // ARESCONNECTION_H

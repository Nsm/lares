#ifndef ARESCONNECTION_H
#define ARESCONNECTION_H

#include <QObject>
#include "giftconnection.h"
#include "aresitem.h"

class AresConnection : public QObject
{
    Q_OBJECT
public:
    AresConnection();
    enum Status{CONNECT, CONNECTING, DISCONNECTED};
    void open();
    void close();
    int search(QString query);
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

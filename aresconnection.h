#ifndef ARESCONNECTION_H
#define ARESCONNECTION_H

#include <QObject>
#include "giftconnection.h"

class AresConnection : public QObject
{
    Q_OBJECT
public:
    AresConnection();
    enum Status{CONNECT, CONNECTING, DISCONNECTED};
    void open();
    void close();
private:
    GIftConnection * giftConnection;
    Status connectionStatus;
    void setStatus(Status status);
    Status getStatus();
private slots:
    void readCommand();
signals:
    void statusChanged(AresConnection::Status newStatus);
};

#endif // ARESCONNECTION_H
